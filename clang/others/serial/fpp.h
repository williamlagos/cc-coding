#ifndef __FPP_H__
#define __FPP_H__

#include <arch/nxp/lpc23xx.h>

#define USE_LED
#define USE_LCD
#define USE_I2C
#define USE_UART

#define SEG(x)					\
  (x * 1000000)
#define MILISEG(x)				\
  (x * 1000)
#define USEG(x)					\
  (x * 1)

typedef unsigned long	 u_int32_t;
typedef long		 int32_t;
typedef unsigned short	 u_int16_t;
typedef short		 int16_t;
typedef unsigned char	 u_int8_t;
typedef char		 int8_t;

/* I2C TMP101 address */
#define TMP101_ADDR		(0x90)

#define CRYSTALFREQ		(12000000)

#ifdef USE_LCD
//#define LCD_E			(0x01000000)
//#define LCD_RS			(0x02000000)
#define LCD_E			(1 << 24)
#define LCD_RS			(1 << 25)
#define LCD_D			(0x000000ff)
#endif /* USE_LCD */

#define BUTTON1			(0x0100)
#define BUTTON2			(0x0200)
#define BUTTON3			(0x0400)
#define BUTTON4			(0x0800)
#define BUTTON5			(0x1000)
#define IS_PRESSED(button) \
(!(FIO4PIN & (button)))


#define SET_BIT(var, pos)			\
  do {						\
    (var) |= (1 << (pos));			\
  } while (0)
#define UNSET_BIT(var, pos)			\
  do {						\
    (var) &= ~(1 << (pos));			\
  } while (0)

#ifdef USE_LED
extern u_int8_t		 leds_state;
#define UPDATE_LED() \
  do {						\
    FIO4CLR = ~(leds_state);			\
    FIO4SET = leds_state;			\
  } while (0)
#define TURN_LED(led, state)			\
  do {						\
    if (state)					\
      SET_BIT(leds_state, (led));		\
    else					\
      UNSET_BIT(leds_state, (led));		\
    UPDATE_LED();				\
  } while (0)
#endif /* USE_LED */

#ifdef USE_LCD
extern int		 line;
#endif /* USE_LCD */

/* Prototypes */
void	 init_board(void);
void	 wait(u_int32_t);
void	 uwait(u_int32_t);
#ifdef USE_I2C
void	 write_I2C(int, int);
int	 read_I2C(int, char *, int);
void	 wait_I2C(unsigned int);
short	 read_temp(void);
#endif /* USE_I2C */
#ifdef USE_LCD
void	 LCD_command(int);
void	 LCD_putchar(int);
void	 LCD_puts(const char *, int);
void	 LCD_writedec(int);
void	 show_temperature(int);
#endif /* USE_LCD */
#ifdef USE_UART
char	 UART0_getchar(void);
void	 UART0_putchar(char);
void	 UART0_puts(const char *, int);
void	 UART0_gets(char *, int);

/* Compatibility with Stemmer stuff */
#define le_texto(txt, nmax)		\
	UART0_gets((txt), (max));
#endif /* USE_UART */

/* Specific stuff DONT TOUCH THIS! */
void	 UNDEF_Routine(void);
void	 SWI_Routine(void);
void	 FIQ_Routine(void);

/*******************************************************
Modulo para usar o I2C
Prototipos do modulo i2c.c
Marcos A. Stemmer
********************************************************/

/* Definindo USA_I2C0 as rotinas vao configurar para usar o i2c0
   Tambem pode-se definir USA_I2C2 para usar o i2c2 */
#define USA_I2C0
//#define USA_I2C2

#ifdef USA_I2C0
#define	I2C_BASE_ADDR	0xE001C000
#endif

#ifdef USA_I2C2
#define	I2C_BASE_ADDR	0xE0080000
#endif

#define	I2cCONSET      (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x00))
#define	I2cSTAT	       (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x04))
#define	I2cDAT	       (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x08))
#define	I2cADR	       (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x0C))
#define	I2cSCLH	       (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x10))
#define	I2cSCLL	       (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x14))
#define	I2cCONCLR      (*(volatile unsigned long *)(I2C_BASE_ADDR + 0x18))

/* Inicializa a interface i2c2 com interrupcao.
Deve ser chamada 1 vez no programa antes de comecar a usar o i2c.*/
void ini_i2c(void);

/* Escreve dados em um dispositivo i2c
i2caddr	Endereco i2c do dispositivo
buf	Local onde os dados estao armazenados
n	Numero de bytes que devem ser escritos
Retorna ZERO em caso de sucesso */
int escreve_i2c(int i2caddr, char *buf, int n);

/* Le dados de um dispositivo i2c
i2caddr	Endereco i2c do dispositivo
buf	Local onde deve armazenar os dados lidos
n	Numero de bytes que devem ser lidos
Retorna ZERO se conseguiu ler */
int	le_i2c(int i2caddr, char *buf, int n);

/* Espera terminar uma transacao i2c (usada internamente)*/
void espera_i2c(int timeout);

/* Escreve apenas um byte no dispositivo i2c. Retorna 0 se conseguiu. */
int escreve_byte_i2c(int i2caddr, int val);

/* Le apenas um byte. Retorna o byte lido ou -1 em caso de erro */
int le_byte_i2c(int i2caddr);

int dig2ascii(int);
void PrByte(int);
void LCDprbyte(int);
void escrevenum(int);
void letexto(char *, int);
int lenumero(const char *);

#endif /* __FPP_H__ */
