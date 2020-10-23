#include "fpp.h"

int		 line = 0;
volatile int	 i2cn;		/* Numero de bytes a ler/escrever */
char		*i2cdados;	/* Buffer de dados lidos ou escritos */
int		 slvaddr;	/* Endereco do dispositivo i2c	*/
u_int8_t	 leds_state = 0;

/* Functions */
void
init_board(void)
{
  /* Misclaneous */
  T1TCR = 0;
  T1PR = (CRYSTALFREQ / 1000) - 1; /* Increments T0PR 1000 times per sec */
  T1TCR = 2;
  T1TCR = 1;

#ifdef USE_LED
  /* LEDs stuff */
  FIO4DIR |= 0xFF;		/* LEDs are write-only */
#endif /* USE_LED */

#ifdef USE_LCD
  /* LCD Stuff */
  FIO4DIR |= (LCD_RS | LCD_E); /* LCD como saida */
  FIO4CLR = LCD_E;
  FIO3DIR |= 0xFF;
  line = 0x80;
  T0TCR = 0;		/* Desabilita T0 */
  T0PR = CRYSTALFREQ / 1000 - 1;	/* Incrementa o contador T0TC 1000 vezes por segundo */
  T0TCR = 2;		/* Inicializa T0 */
  T0TCR = 1;		/* Habilita T0  */
  wait(1000);

  LCD_command(0x38);
  LCD_command(1);		/* Clear */
  LCD_command(0x0e);		/* Cursor: _ */
#endif /* USE_LCD */

  MEMMAP = 2;


  PCONP |=0x04000080;		/* Turn on I2C0 & I2C2 */
  PINSEL0 &= 0xffafffff;
  PINSEL0 |= 0x00a00000;	/* Select pins: SDA2 & SCL2 */
  I22CONCLR = 0xff;
  I22CONSET = 0x40;		/* Turn I2C-2 to master */
  I22SCLH = 100;		/* High time SCL */
  I22SCLL = 100;		/* Low time SCL */
  write_I2C(1, 0x60);
#ifdef USE_UART
  /* UART0 Initialization */
  PCLKSEL0 = (PCLKSEL0 & (~0xc0)) | 0x40; /* divide por 1 no PCLK da UART0 */
  PCONP |= 8;		/* Liga energia da UART0 */
  PINSEL0 |= (PINSEL0 & (~0xf0)) | 0x50;	/* Seleciona pinos TxD0 e RxD0 */
  U0FCR = 0x7;	/* Habilita as FIFOs e reset */
  U0LCR = 0x83;	/* Habilita acesso ao divisor de baud-rate (DLAB) */
  U0DLL = ((CRYSTALFREQ / BAUDRATE + 8) >> 4) & 0xff;
  U0DLM = ((CRYSTALFREQ / BAUDRATE) >> 12) & 0xff;
  U0LCR = 0x03;	/* Configura UART0 como 8N1 */
#endif /* USE_UART */

#ifdef USE_RTC
  /* Clock initialization */
  /* Se CLOCKRTC for definido usa-se oscilsdor espencial de 32768Hz
   * Se nao for definido usa o clock de 12MHz -
   */
#define CLOCKRTC
  CCR = 0; /* Stop clock */

  if (HOUR > 23)
    HOUR = 12;
  if (MIN > 59)
    MIN = 0;
  if (SEC > 59)
    SEC = 0;

#ifdef CLOCKRTC
  CCR = 0x11;	/* Use RTC oscilator 32768Hz */
#else
  PREINT = (CRYSTALFREQ >> 17) - 1;
  PREFRAC = ((CRYSTALFREQ >> 2) & 0x7fff);
  CCR = 1;		/* Use 12MHz with scheduler */
#endif /* CLOCKRTC */
#endif /* USE_RTC */
}

void
wait(u_int32_t time)
{
  volatile int		 x;
  while(time--) {
    x++;
    x--;
  }
}

void
uwait(u_int32_t time)
{
  unsigned int		tf;

  /* T0TC is a tick counter */
  tf = T1TC + time;
  /* While tick count isn't at our target, wait. Else exit the function */
  while(tf != T1TC)
    if (U1LSR & 1)
      break;
}

#ifdef USE_I2C
/* Write 2 bytes to I2C.
 * val < 0 writes only data.
 */
void
write_I2C(int data, int val)
{
  int		 done, timeout;

  done = 1;
  timeout = 1000;

  /* Initiate transaction: Send address 0x96 to write to TMP100 */
  I22CONCLR = 0xFF;
  I22CONSET = 0x60;
  do {
    switch(I22STAT) {
    case 0x08: /* Device Ready; Send data */
      I22CONCLR=0x20;
      /* FALLTHROUGH */
    case 0x20: /* Device ERROR: resend */
      I22DAT = TMP101_ADDR;
      I22CONCLR = 8;
      timeout = 1000;
      break;
    case 0x18: /* Address ready: send data */
      I22DAT = data;
      I22CONCLR = 8;
      timeout = 1000;
      break;
    case 0x28: /* Data ready: stop sending */
      if (val >= 0) {
	I22DAT = val;
	val -= 0x100;
      } else
	I22CONSET = 0x10;

      I22CONCLR = 8;
      done = 0;
      timeout = 1000;
      break;
    }
  } while(done && --timeout);

  timeout = 8000;
  while(!(I22STAT & 8) && --timeout);
}

int
read_I2C(int i2caddr, char *buf, int n)
{
  i2cdados = buf;
  slvaddr = i2caddr | 1;	/* Endereco de leitura	*/
  i2cn = n;		/* Vai ler n bytes	*/
  I2cCONCLR = 0xbf;	/* Limpa comando */
  I2cCONSET = 0x20;	/* Inicia a leitura	*/
  wait_I2C(800);	/* Espera terminar de ler */
  return i2cn;
}

/* Espera ate terminar uma transacao i2c */
void
wait_I2C(unsigned int t)
{
  t += T0TC;

  while ((t != T0TC) && (i2cn > 0));	/* Espera ate que i2cn==0 */

  t = T0TC + 40;
  while (t != T0TC);
}

/* No I2C numero 0x96 tem um termometro tipo TMP100 da TI */
short
read_temp(void)
{
  short		 temp;
  int		 done, timeout;

  write_I2C(0, -1);

  done = 2;
  temp = 0;
  timeout = 1000;

  /* Fase 2: Read temperature (2 bytes) */
  I22CONCLR = 0xFF;
  I22CONSET = 0x60;
  do {
    switch(I22STAT) {
    case 0x08:
      I22CONCLR = 0x20;
    case 0x20:
      I22DAT = TMP101_ADDR + 1;
      I22CONCLR = 8;
      timeout = 1000;
      break;
    case 0x40:
      I22CONSET = 4;
      I22CONCLR = 8;
      timeout = 1000;
      break;
    case 0x50:
      temp = (temp << 8) | I22DAT;
      if (!(--done))
	I22CONSET = 0x10;
      I22CONCLR = 8;
      timeout = 1000;
      break;
    }
  } while(done && --timeout);
  return (temp >> 4);
}
#endif /* USE_I2C */

#ifdef USE_LCD
/* Escreve um caractere no display LCD */
void
LCD_putchar(int c)
{
  if (c == '\n') {
    line ^= 0x40;
    LCD_command(line);
  }
  if (c < 0x20)
    return;

  uwait(5);
  FIO3PIN0 = c;
  FIO4SET = LCD_RS;
  FIO4SET = LCD_E;
  FIO4CLR = LCD_E;
}

void
LCD_command(int c)
{
  uwait(5);
  FIO3PIN0 = c;
  FIO4CLR = LCD_RS;
  FIO4SET = LCD_E;
  FIO4CLR = LCD_E;
}

void
LCD_puts(const char *str, int strlen)
{
  int		 i;

  for (i = 0; i < strlen && str[i] != 0; i++)
    LCD_putchar(str[i]);
}

void
LCD_writedec(int val)
{
  LCD_putchar((val / 10) + '0');
  LCD_putchar((val % 10) + '0');
}

int
dig2ascii(int c)
{
	c = '0' + (c & 0xf);
	if (c > '9')
		c += 'A' - '9' - 1;
	return (c);
}

void
LCDprbyte(int c)
{
	LCD_putchar(dig2ascii(c >> 4));
	LCD_putchar(dig2ascii(c));
}
#endif /* USE_LCD */

#ifdef USE_UART
char
UART0_getchar(void)
{
  while ((U0LSR & 1) == 0)
    /* NOTHING */;
  return (U0RBR);
}

void
UART0_gets(char *str, int strlen)
{
  int	 pos, c;
  pos = 0;
  do {
	c = UART0_getchar();
	if (c == 0x7f)
	  c = 8;
	//UART0_putchar((char) c);
	if (c == 8 && pos != 0)
	  pos--;
	else if(pos < strlen)
	  str[pos++] = c;
  } while(c != '\n' && c != '\r');
  //UART0_putchar('\n');
  str[pos - 1] = '\0';
}

void
UART0_putchar(char c)
{
  while((U0LSR & 0x20) == 0)
    /* NOTHING */;
  U0THR = c;
}

void
UART0_puts(const char *str, int strlen)
{
  int		 i;

  for (i = 0; i < strlen && str[i] != 0; i++)
    UART0_putchar(str[i]);
}

/* Escreve um numero decimal */
void
escrevenum(int num)
{
	char	 digs[16];
	int	 nd;

	nd = 0;
	if (num < 0) {
		UART0_putchar('-');
		num = -num;
	}
	do {
		digs[nd++] = (num % 10) + '0';
		num /= 10;
	} while(num);

	while (nd)
		UART0_putchar(digs[--nd]);
}

void
PrByte(int c)
{
	UART0_putchar(dig2ascii(c >> 4));
	UART0_putchar(dig2ascii(c));
}
#endif /* USE_UART */

#if defined(USE_LCD) && defined(USE_UART)
void
show_temperature(int num)
{
  char		 digs[16];
  int		 nd;

  nd = 0;
  num *= 625;
  if (num < 0) {
    LCD_putchar('-');
    num = -num;
  }

  do {
    digs[nd++] = (num % 10) + '0';
    num /= 10;
  } while(num);

  while (nd < 5)
    digs[nd++] = '0';
  while (nd > 4)
    LCD_putchar(digs[--nd]);

  LCD_putchar(',');
  LCD_putchar(digs[--nd]);
  LCD_putchar(digs[--nd]);
}
#endif /* USE_LCD && USE_UART */

int
lenumero(const char *str)
{
	int	 x, d, s;
	x = s = 0;

	while(*str == ' ')
		str++;

	if (*str == '-') {
		s=1;
		str++;
	}

	while (1) {
		d = *str++;
		if (d < '0' || d > '9')
			break;
		x = x * 10 + d - '0';
	}
	return ((s) ? (-x) : (x));
}

/* Specific stuff DONT TOUCH THIS!
 *
 * Estas rotinas sao chamados pelo crt.S.
 * Devem existir, mas ainda nao estao sendo usadas
 */
void UNDEF_Routine(){}
void SWI_Routine(){}
void FIQ_Routine(){}
