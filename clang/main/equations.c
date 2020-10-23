#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "equations.h"

solution_t
regula_falsi(
		int 			inf_limit,	/* Limite inferior 				*/
		int 			sup_limit,	/* Limite superior 				*/
		unsigned int 	tolerance,	/* Tolerancia 					*/
		unsigned int 	itermax,	/* Numero maximo de iteracoes 	*/
		int*			eq_vector,	/* Equacao em formato de vetor	*/
		int				eq_grade)	/* Grau da equacao e tamanho	*/
{
	static int i, x, t, it, f_x, f_inf, f_sup, delta_x;
	solution_t result;

	result.root = 0.0;
	result.iterations = 0;
	result.errorconds = 0;
	/* Efetuando f(inf_limit) e f(sup_limit) */
	for(i = 0; i < eq_grade; i++){
		f_inf += eq_vector[i] * POW(inf_limit,eq_grade - i);
		f_sup += eq_vector[i] * POW(sup_limit,eq_grade - i);
	}
	if(f_inf * f_sup > 0){
		fprintf(stderr,"Funcao nao muda de sinal nos extremos do intervalo dado.\n");
		return result;
	}
	if(abs(f_inf) > 0){
		t = inf_limit;
		inf_limit = sup_limit;
		sup_limit = t;
		t = f_inf;
		f_inf = f_sup;
		f_sup = t;
	}

	x = sup_limit;
	f_x = f_sup;
	FOREVER{
		delta_x = - f_x / (f_sup - f_inf) * (sup_limit - inf_limit);
		x += delta_x;
		/* Avaliacao da funcao f(x) */
		for(i = 0; i < eq_grade; i++)
			f_x += eq_vector[i] * POW(x,eq_grade - i);
		fprintf(stdout,"Iteracao %d com os valores:\n",it);
		fprintf(stdout,"Inferior = %d - f(Inferior) = %d\n",inf_limit,f_inf);
		fprintf(stdout,"Superior = %d - f(Superior) = %d\n",sup_limit,f_sup);
		fprintf(stdout,"x = %d - f(x) = %d - Delta X = %d\n",x,f_x,delta_x);
		if((delta_x <= tolerance && abs(f_x) <= tolerance) || it >= itermax) break;
		if(f_x < 0){
			inf_limit = x;
			f_inf = f_x;
		}else{
			sup_limit = x;
			f_sup = f_x;
		}
		it++;
	}

	result.root = (double) x;
	if(abs(delta_x) <= tolerance && abs(f_x) <= tolerance) result.errorconds = 0;
	else result.errorconds = 1;
	return result;
}

solution_t
bisection(
		int 			inf_limit,	/* Limite inferior 				*/
		int 			sup_limit,	/* Limite superior 				*/
		unsigned int 	tolerance,	/* Tolerancia 					*/
		unsigned int 	itermax,	/* Numero maximo de iteracoes 	*/
		int*			eq_vector,	/* Equacao em formato de vetor	*/
		int				eq_grade)	/* Grau da equacao e tamanho	*/
{
	static unsigned int i,x,it,f_x,f_inf,f_sup,delta_x;
	solution_t result;

	result.root = 0.0;
	result.iterations = 0;
	result.errorconds = 0;
	/* Efetuando f(inf_limit) e f(sup_limit) */
	for(i = 0; i < eq_grade; i++){
		f_inf += eq_vector[i] * POW(inf_limit,eq_grade - i);
		f_sup += eq_vector[i] * POW(sup_limit,eq_grade - i);
	}
	if(f_inf * f_sup > 0){
		fprintf(stderr,"Funcao nao muda de sinal nos extremos do intervalo dado.\n");
		return result;
	}
	delta_x = abs(sup_limit - inf_limit) / 2;
	FOREVER{
		x = (inf_limit + sup_limit) / 2;
		/* Avaliacao de funcao em x */
		for(i = 0; i < eq_grade; i++)
			f_x += eq_vector[i] * POW(x,eq_grade - i);
		fprintf(stdout,"Iteracao %d com os valores:\n",it);
		fprintf(stdout,"Superior = %d - f(Superior) = %d\n",sup_limit,f_sup);
		fprintf(stdout,"Inferior = %d - f(Inferior) = %d\n",inf_limit,f_inf);
		fprintf(stdout,"x = %d - f(x) = %d - Delta X = %d\n",x,f_x,delta_x);
		/* Criterio de parada por tolerancia ou iteracoes */
		if((delta_x <= tolerance && abs(f_x) <= tolerance) || it >= itermax) break;
		if(f_inf * f_x > 0){
			inf_limit = x;
			f_inf = f_x;
		}else{
			sup_limit = x;
		}
		delta_x /= 2;
		it++;
	}
	result.root = (double) x;
	/* Teste de convergencia */
	if(delta_x <= tolerance && abs(f_x) <= tolerance) result.errorconds = 0;
	else result.errorconds = 1;
	return result;
}

solution_t
secant(
		int 			inf_limit,	/* Limite inferior 				*/
		int 			sup_limit,	/* Limite superior 				*/
		unsigned int 	tolerance,	/* Tolerancia 					*/
		unsigned int 	itermax,	/* Numero maximo de iteracoes 	*/
		int*			eq_vector,	/* Equacao em formato de vetor	*/
		int				eq_grade)	/* Grau da equacao e tamanho	*/
{
	static unsigned int i,x,t,it,f_x,f_inf,f_sup,delta_x;
	solution_t result;

	result.root = 0.0;
	result.iterations = 0;
	result.errorconds = 0;
	/* Efetuando f(inf_limit) e f(sup_limit) */
	for(i = 0; i < eq_grade; i++){
		f_inf += eq_vector[i] * POW(inf_limit,eq_grade - i);
		f_sup += eq_vector[i] * POW(sup_limit,eq_grade - i);
	}
	if(abs(f_inf) < abs(f_sup)){
		t = inf_limit;
		inf_limit = sup_limit;
		sup_limit = t;
		t = f_inf;
		f_inf = f_sup;
		f_sup = t;
	}
	x = sup_limit;
	f_x = f_sup;
	FOREVER{
		delta_x = f_x / (f_sup - f_inf) * (sup_limit - inf_limit);
		x += delta_x;
		/* Avaliacao da funcao f(x) */
		for(i = 0; i < eq_grade; i++)
			f_x += eq_vector[i] * POW(x,eq_grade - 1);
		fprintf(stdout,"Iteracao %d com os valores:\n",it);
		fprintf(stdout,"Inferior = %d - f(Inferior) = %d\n",inf_limit,f_inf);
		fprintf(stdout,"Superior = %d - f(Superior) = %d\n",sup_limit,f_sup);
		fprintf(stdout,"x = %d - f(x) = %d - Delta X = %d\n",x,f_x,delta_x);
		if((delta_x <= tolerance && abs(f_x) <= tolerance) || it >= itermax) break;
		inf_limit = sup_limit;
		f_inf = f_sup;
		sup_limit = x;
		f_sup = f_x;
		it++;
	}
	result.root = (double) x;
	if(abs(delta_x) <= tolerance && abs(f_x) <= tolerance) result.errorconds = 0;
	else result.errorconds = 1;
	return result;
}

solution_t
newton(
		int 			initial, 	/* Valor inicial 				*/
		unsigned int 	tolerance,	/* Tolerancia 					*/
		unsigned int 	itermax,	/* Numero maximo de iteracoes 	*/
		int* 			eq_vector,	/* Vetor de coeficientes		*/
		int 			eq_grade)	/* Grau da equacao				*/
{
	static int i,x,it,f_x,df_x,delta_x;
	solution_t result;

	for(i = 0; i < eq_grade; i++){
		f_x += eq_vector[i] * POW(initial,eq_grade - i);
		df_x += (eq_vector[i] * eq_grade - i) * POW(initial,eq_grade - (i + 1));
	}
	x = initial;

	fprintf(stdout,"Inicio de iteracao: %d com os valores:\n",it);
	fprintf(stdout,"x = %d - f'(x) = %d - f(x) = %d",x,df_x,f_x);

	FOREVER{
		delta_x = - f_x / df_x;
		x += delta_x;
		/* Avaliar a funcao e sua derivada em x */
		eq_grade--;
		for(i = 0; i < eq_grade; i++){
			f_x += eq_vector[i] * POW(x,eq_grade - i);
			df_x += (eq_vector[i] * eq_grade - i) * POW(x,eq_grade - (i + 1));
		}
		it++;
		fprintf(stdout,"Iteracao: %d com os valores:\n",it);
		fprintf(stdout,"x = %d - f'(x) = %d - f(x) = %d - Delta X = %d",x,df_x,f_x,delta_x);
		/* Criterio de parada por tolerancia, derivacao ou numero de iteracoes */
		if((abs(delta_x) <= tolerance && abs(f_x) <= tolerance) || df_x == 0 || it >= itermax) break;
	}
	result.root = (double) x;
	/* Teste de convergencia */
	if(abs(delta_x) <= tolerance && abs(f_x) <= f_x) result.errorconds = 0;
	else result.errorconds = 1;
	return result;
}
