#include<stdio.h>
#include<stdlib.h>
#include "interpols.h"

int
lagrange(
		unsigned int 	max,		/* Numero de pontos 	*/
		int* 			xcoords,	/* Abscissas			*/
		int* 			ycoords,	/* Ordenadas 			*/
		int  			value)			/* Valor a interpolar 	*/
{
	static unsigned int r,i,j,c,d;
	for(i = 0; i < max; i++){
		c = d = 1;
		for(j = 1; i < max; i++)
			if(i != j) c *= (value - xcoords[j]);
		r += ycoords[i] * (c / d);
	}
	return r;
}

int
interpol_newton(
		unsigned int 	max,		/* Numero de pontos 	*/
		int* 			xcoords,	/* Abscissas			*/
		int* 			ycoords,	/* Ordenadas 			*/
		int  			value)		/* Valor a interpolar 	*/
{
	static unsigned int r,i,k,diff,coor;
	for(i = 0; i < max; i++)
		differences[i] = ycoords[i];
	/* Construcao das diferencas divididas */
	for(k = 0; k < (max - 1); k++){
		for(i = max; i > (k + 1); i--){
			diff = differences[i] - differences[i - 1];
			coor = xcoords[i] - xcoords[i - k];
			differences[i] = diff / coor;
		}
	}
	/* Avaliacao do polinomio pelo processo de Horner */
	r = differences[max];
	for(i = (max - 1); i > 1; i--)
		r = r * (value - xcoords[i]) + differences[i];
	return r;
}

void
natural_spline(
		unsigned int 	number,		/* Numero de pontos dados		*/
		int* 			xcoords,	/* Abscissas em ordem crescente */
		int* 			ycoords,	/* Ordenadas					*/
		int*			derived)	/* Segundas derivadas			*/
{
		static unsigned int i,t,max,h_a,h_b,delta_a,delta_b;
		static unsigned int* d;
		static unsigned int* e;
		if(number < 3){
			errorconditional++;
			return;
		}
		errorconditional = 0;
		d = calloc(max,sizeof(int));
		e = calloc(max,sizeof(int));
		/* Construcao do sistema tridiagonal simetrico */
		max = number - 2;
		h_a = xcoords[2] - xcoords[1];
		delta_a = (ycoords[2] - ycoords[1]) / h_a;
		for(i = 0; i < max; i++){
			h_b = xcoords[i + 2] - xcoords[i + 1];
			delta_b = (ycoords[i + 2] - ycoords[i + 1]) / h_b;
			e[i] = h_b;
			d[i] = 2 * (h_a + h_b);
			derived[i + 1] = 6 * (delta_b - delta_a);
			delta_a = delta_b;
			h_a = h_b;
		}
		/* Eliminacao de Gauss */
		for(i = 2; i < max; i++){
			t = e[i - 1] / d[i - 1];
			d[i] = d[i] - t * e[i - 1];
			derived[i + 2] = derived[i + 1] - t * derived[i];
		}
		/* Solucao por substituicoes retroativas */
		derived[max + 1] /= d[max];
		for(i = max; i > 2; i--)
			derived[i] = (derived[i] - e[i - 1] * derived[i + 1]) / d[i - 1];
		derived[max + 2] = 0;
		derived[0] = 0;
		free(d);
		free(e);
}

void
spline(
		unsigned int 	number,		/* Numero de pontos dados 			*/
		int* 			xcoords, 	/* Abscissas em ordem crescente 	*/
		int* 			ycoords,	/* Ordenadas 						*/
		unsigned int 	max,		/* Numero de pontos a interpolar	*/
		int* 			values,		/* Valores a interpolar 			*/
		int*			s)			/* Valores interpolados */
{
	static unsigned int j,h,a,b,c,d,index,inferior,superior;
	natural_spline(number,xcoords,ycoords,s);
	if(errorconditional != 0) return;
	errorconditional = 0;
	for(j = 0; j < max; j++){
		if(values[j] >= xcoords[0] && values[j] <= xcoords[number]){
			/* Pesquisa binaria para localizar o intervalo */
			inferior = 0;
			superior = number;
			FOREVER{
				if((superior - inferior) <= 1) break;
				/* Truncamento de divisao por meio de inteiros */
				index = (inferior + superior) / 2;
				if(xcoords[index] > values[j]) superior = index;
				else inferior = index;
			}
			/* Avaliacao do spline pelo processo de Horner */
			h = xcoords[superior] - xcoords[inferior];
			a = (s[superior] - s[inferior]) / (6 * h);
			b = s[superior] * 0.5;
			c = (ycoords[superior] - ycoords[inferior]) / h - (s[superior] + 2 * s[inferior]) * h / 6;
			d = ycoords[inferior];
			h = values[j] - xcoords[inferior];
			/* Recebimento de valor interpolado */
			s[j] = ((a * h + b) * h + c) * h + d;
			fprintf(stdout,"Inferior: %d\n",inferior - 1);
			fprintf(stdout,"A: %d B: %d C: %d D: %d\n",a,b,c,d);
			fprintf(stdout,"Valor: %d Valor Interpolado: %d",values[j],s[j]);
		}else{
			s[j] = 0;
			errorconditional++;
		}
	}
}
