/*******************************************************
Modulo para usar o canal 2 de I2C
********************************************************/
#include "fpp.h"


char		*i2cdados;	/* Buffer de dados lidos ou escritos */
int		 slvaddr;	/* Endereco do dispositivo i2c	*/
volatile int	 i2cn;		/* Numero de bytes a ler/escrever */

void IRQ_i2c(void) __attribute__ ((interrupt("IRQ")));

/* Declaracoes especiais para rotinas de atendimento a interrupcoes*/
void SWI_Routine(void) __attribute__ ((interrupt("SWI")));
void IRQ_Routine(void) __attribute__ ((interrupt("IRQ")));
void FIQ_Routine(void) __attribute__ ((interrupt("FIQ")));

/* Macros para habilitar/desabilitar IRQ/FIQ no CPSR */
#define habilitaFIQ() asm volatile(\
	"mrs r3, cpsr\n" \
	"bic r3, r3, # 0x40\n" \
	"msr cpsr, r3\n")

#define desabilitaFIQ() asm volatile(\
	"mrs r3, cpsr\n" \
	"orr r3, r3, # 0x40\n" \
	"msr cpsr, r3\n")

#define habilitaIRQ() asm volatile(\
	"mrs r3, cpsr\n" \
	"bic r3, r3, # 0x80\n" \
	"msr cpsr, r3\n")

#define desabilitaIRQ() asm volatile(\
	"mrs r3, cpsr\n" \
	"orr r3, r3, # 0x80\n" \
	"msr cpsr, r3\n")


/*
A rotina de interrupcao do I2C implementa uma maquina de estados.
Dependendo do valor do I2cSTAT sabe o que foi feito e qual e' a
proxima coisa a fazer. */
void
IRQ_i2c(void)
{
	static int	k;

	I2cCONSET = 4;		/* Normalmente responde ACK */
	switch(I2cSTAT) {
	case 0:
	case 0x20:	/* Erro */
	case 0x30:			/* Dado foi escrito recebendo NACK */
	case 0x48:			/* Endereco de leitura recebeu NACK */
		I2cCONSET = 0x10;	/* Gera STOP */
		i2cn = -1;		/* i2cn=-1 indica erro */
		break;
	case 8:		/* Terminou de enviar o START bit */
		I2cCONCLR = 0x20;
		I2cDAT = slvaddr;	/* Escreve endereco */
		k=0;	/* Inicializa indice dos dados */
		break;
	case 0x18:	/* Enviou endereco de escrita recebendo ACK */
	case 0x28:	/* Escreveu dado recebendo ACK */
		/* Escreve mais dados */
		if(i2cn) {
			 I2cDAT = i2cdados[k++];
			 i2cn--;
		} else
			I2cCONSET=0x14;	/* Fim dos dados: gera STOP */
		break;
	case 0x40:		/* Enviou endereco de leitura e recebeu ACK */
		/* Prepara para iniciar a leitura de dados */
		i2cdados[0] = I2cDAT;
		k = 0;		/* Le lixo so para iniciar */
		if (i2cn==1)
			I2cCONCLR=4; /* So 1 dado responde NACK */
		break;
	case 0x50:			/* Dado recebido enviando ACK */
		i2cdados[k++] = I2cDAT;	/* Le o proximo dado */
		/* Se for o ultimo envia NACK */
		if (!(--i2cn))
			I2cCONCLR=4;
		break;
	case 0x58:			/* Leu enviando NACK */
		i2cdados[k++] = I2cDAT;	/* Le o ultimo dado */
		i2cn = 0;		/* Leu todos os dados */
		I2cCONSET = 0x10;	/* Gera STOP */
		break;
	}
	I2cCONCLR = 8;		/* Limpa o indicador de interrupcao do I2C */
	VICVectAddr = 0;	/* Limpa o vetor do VIC */
}

/* Espera ate terminar uma transacao i2c */
void
espera_i2c(int t)
{
	UART0_putchar('L');
	t += T2TC;
	/* Espera ate que i2cn==0 */
	while ((t!=T2TC) && (i2cn > 0))
		/* NOTHING */UART0_putchar('M');;

UART0_putchar('N');
	t = T2TC + 40;
	UART0_putchar('O');
	while (t != T0TC);
	UART0_putchar('P');
}

/* Inicializa o I2C com interrupcao */
void
ini_i2c(void)
{
	T0TCR = 0;              /* Desabilita T0 */
	T0PR = CRYSTALFREQ / 1000 - 1; /* Incrementa o contador T0TC 1000 vezes por segundo */
	T0TCR = 2;      /* Inicializa T0 */
	T0TCR = 1;      /* Habilita T0  */

	PCONP |= 0x04000080;	/* Liga energia do i2c0 e i2c2 */
	I2cCONCLR = 0xff;
	I2cCONSET = 0x40;	/* Habilita o i2c2 um modo mestre */
	I2cSCLH = 100;	/* Tempo alto do SCL	*/
	I2cSCLL = 100;	/* Tempo baixo do SCL	*/

	/* Habilita a interrupcao do i2c2 como IRQ no VIC	*/
	desabilitaIRQ();	/* Definida no #include "vic_cpsr.h"	*/
#ifdef USA_I2C2
	PINSEL0 &= 0xffafffff;
	PINSEL0 |= 0x00a00000;
	VICIntSelect &= ~0x40000000;	/* i2c2=bit 30 como IRQ	*/
	VICIntEnable = 0x40000000;	/* Habilita int do i2c2 no VIC*/
	VICVectAddr30 = (int)IRQ_i2c;	/* Vetor para atendimento do I2C2 */
#endif
#ifdef USA_I2C0
	PINSEL1 &= 0xfd7fffff;
	PINSEL1 |= 0x01400000;
	VICIntSelect &= ~0x200;	/* i2c0=bit 9 como IRQ	*/
	VICIntEnable = 0x200;	/* Habilita int do i2c0 no VIC*/
	VICVectAddr9 = (int)IRQ_i2c;	/* Vetor 9 para atendimento do I2C0 */
#endif

	i2cn = 0;
	habilitaIRQ();
	I2cCONSET = 0x10;
}

/* Le dados de um dispositivo i2c
 * addri2c	Endereco i2c do dispositivo
 * buf	Local onde deve armazenar os dados lidos
 * n	Numero de bytes que devem ser lidos
 * Retorna ZERO se conseguiu ler
 */
int
le_i2c(int i2caddr, char *buf, int n)
{
	i2cdados = buf;
	slvaddr = i2caddr | 1;	/* Endereco de leitura	*/
	i2cn = n;		/* Vai ler n bytes	*/
	I2cCONCLR = 0xbf;	/* Limpa comando */
	I2cCONSET = 0x20;	/* Inicia a leitura	*/
	espera_i2c(800);	/* Espera terminar de ler */
	return (i2cn);
}

/* Escreve dados em um dispositivo i2c
 * addri2c	Endereco i2c do dispositivo
 * buf	Local onde os dados estao armazenados
 * n	Numero de bytes que devem ser escritos
 * Retorna ZERO em caso de sucesso
 */
int
escreve_i2c(int addri2c, char *buf, int n)
{
	i2cdados = buf;
	slvaddr = addri2c & 0xFE;
	i2cn = n;
	I2cCONCLR = 0xBF;
	I2cCONSET = 0x20;
	espera_i2c(2000);
	return (i2cn);
}

/* Escreve apenas um byte. Retorna 0 se conseguiu. */
int
escreve_byte_i2c(int addri2c, int dado)
{
	char	 buf[2];
	buf[0] = dado;
	return (escreve_i2c(addri2c, buf, 1));
}

/* Le apenas um byte. Retorna o byte lido ou -1 em caso de erro */
int
le_byte_i2c(int addri2c)
{
	unsigned char	 buf[2];
	if (le_i2c(addri2c, buf, 1))
		return (-1);
	return (buf[0]);
}
