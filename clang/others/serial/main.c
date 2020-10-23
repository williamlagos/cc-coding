#include "fpp.h"

static void
blink_leds(int times)
{
	int	 i;

blink:
	for (i = 0; i < 8; i++)
		TURN_LED(i, 0);
	uwait(100);
	for (i = 0; i < 8; i++)
		TURN_LED(i, 1);
	if (--times > 0)
		goto blink;
}


int
main(int argc, char *argv[])
{
	int		 i, c, done;
	int		 offset;
	char	 buf[128], str[64];
	short	 temp;

	i = 0;
	offset = 0;
	init_board();

read_input:
	if (IS_PRESSED(BUTTON1)) {
		UART0_puts("_BALANCE:1_", 64);
		UART0_gets(str, sizeof(str));
		LCD_command(1);
		LCD_puts(str, sizeof(str));
		LCD_putchar('\n');
		temp = read_temp();
		show_temperature(temp);
	} else if (IS_PRESSED(BUTTON2)) {
		UART0_puts("_RECHARGE:1:", 64);
		escrevenum(leds_state);
		UART0_puts("_", 64);
		UART0_gets(str, sizeof(str));
		LCD_command(1);
		LCD_puts(str, sizeof(str));
		LCD_putchar('\n');
		temp = read_temp();
		show_temperature(temp);
	} else if (IS_PRESSED(BUTTON3)) {
		UART0_puts("_DISCHARGE:1:", 64);
		escrevenum(leds_state);
		UART0_puts("_", 64);
		UART0_gets(str, sizeof(str));
		LCD_command(1);
		LCD_puts(str, sizeof(str));
		LCD_putchar('\n');
		temp = read_temp();
		show_temperature(temp);
	} else if (IS_PRESSED(BUTTON4)) {
		leds_state++;
		UPDATE_LED();
		uwait(1000);
	} else if (IS_PRESSED(BUTTON5)) {
		leds_state--;
		UPDATE_LED();
		uwait(1000);
	}
	goto read_input;

	/* NOTREACHED */
	return (0);
}


#if 0
#define ERRSTR "*** ERRO ***\n"
#define INSCAR "Insira o cartao\n"
#define ERRWRT "Erro na escrita\n"
#define IDINPT "Digite com ID do cartao para cadastro: \n"
#define SLINPT "Digite o valor a acrescentar ao saldo: \n"

#define memset(ptr, value, ptr_len)			\
	do {						\
		int	 __i;				\
		for (__i = 0; __i < (int)(ptr_len); __i++)	\
			(ptr)[i] = (value);		\
	} while (0)
#define bzero(ptr, ptr_len)				\
	memset((ptr), 0, (ptr_len))

#define CODE_AUDITION		(0)
#define DPRINTF(msg)					\
	do {						\
		if (CODE_AUDITION)			\
			UART0_puts((msg),			\
			    sizeof((msg)));		\
	} while (0)

int		 x;

static void
read_card(int off, char *buf)
{
	LCD_command(1);
	LCD_puts(INSCAR, sizeof(INSCAR));
	DPRINTF(INSCAR);
	while (FIO0PIN & (1 << 21));

	DPRINTF("AQUI1\n");
	/* Depois de qualquer operacao efetua uma leitura */
	buf[0] = off;
	/* Escreve o offset (endereco no smcard) */
	escreve_i2c(0xa0, buf, 1);
	DPRINTF("AQUI2\n");

	/* Le 16 bytes a partir do offset */
	le_i2c(0xa0, buf, 16);
	buf[16] = '\0';
	DPRINTF("AQUI3\n");
	
	for (x = 0; x < 16; x++)
		PrByte(buf[x]);
}

static void
write_card(int off, char *buf)
{
	LCD_command(1);
	LCD_puts(INSCAR, sizeof(INSCAR));
	DPRINTF(INSCAR);
	while (FIO0PIN & (1 << 21));

	buf[0] = off;
	escreve_i2c(0xa0, buf, 17);
}

	bzero(buf, sizeof(buf));

	done = 0;
	c = UART0_getchar();
	switch (c) {
	case 'w':
		UART0_puts(IDINPT, sizeof(IDINPT));
		UART0_gets(str, sizeof(str));
		DPRINTF("Escrevendo no cartao...\n");
		write_card(offset, str);
		done = 1;
		break;
	case 'r':
		DPRINTF("Lendo cartao...\n");
		read_card(offset, buf);
		LCD_puts(buf, 16);
		UART0_puts(buf, 16);
		done = 1;
		break;
	case '+':
		DPRINTF("Aumentando offset\n");
		offset += 16;
		if (offset > 32)
			offset = 0;
		break;
	case '-':
		DPRINTF("Diminuindo offset\n");
		offset -= 16;
		if (offset < 0)
			offset = 0;
		break;
	default:
#endif
