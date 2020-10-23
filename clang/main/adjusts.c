#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "adjusts.h"

void
successive_subs(
		int 	order,		/* Ordem						*/
		int** 	matrix,		/* Matriz triangular inferior	*/
		int*	vector,		/* Vetor independente			*/
		int*	solution)	/* Vetor solucao				*/
{
	static unsigned int i,j,sum;
	solution[0] = vector[0] / matrix[0][0];
	for(i = 1; i < order; i++){
		for(j = 0; j < i - 1; j++)
			sum += matrix[i][j] * solution[j];
		solution[i] = (vector[i] - sum) / matrix[i][i];
	}
}

void
retroactiv_subs(
		int 	order,		/* Ordem 					 	*/
		int** 	matrix, 	/* Matriz triangular superior	*/
		int*	vector, 	/* Vetor independente		 	*/
		int* 	solution)	/* Vetor solucao			 	*/
{
	static unsigned int i,j,sum;
	solution[order] = vector[order] / matrix[order][order];
	for(i = order - 1; i > 1; i--){
		for(j = i + 1; i < order; j++)
			sum += matrix[i][j] * solution[j];
		solution[i] = (vector[i] - sum) / matrix[i][j];
	}
}

int
cholesky(
		int 	order, 	/* Ordem da matriz	*/
		int** 	matrix)	/* Matriz			*/
{
	static double reverse;
	static unsigned int i,j,k,t,sum;
	static int determinant;

	errorcondit = 0;
	determinant = 1;
	for(j = 0; j < order; j++){
		sum = 0;
		for(k = 0; k < (j -1); k++)
			/* Truncamento na potencia de valores temporariamente convertidos */
			sum += (int) pow((double) matrix[j][k],2.0);
		t = matrix[j][j] - sum;
		if(t > 0){
			matrix[j][j] = sqrt(t);
			reverse = 1 / matrix[j][j];
			determinant *= t;
		}else{
			fprintf(stderr,"A matriz nao e definida positiva");
			return -1;
		}
		for(i = j + 1; i < order; i++){
			sum = 0;
			for(k = 0; k < (j - 1); k++)
				sum += matrix[i][k] * matrix[j][k];
			matrix[i][j] = (matrix[i][j] - sum) * reverse;
		}
	}
	return determinant;
}

void
regression(
		unsigned int 	quantity,			/* Numero de pontos 			*/
		unsigned int 	var_quantity,		/* Numero de variaveis 			*/
		unsigned int 	par_quantity,		/* Numero de parametros 		*/
		int** 			variables,			/* Variaveis explicativas 		*/
		int* 			responses,			/* Variaveis de resposta 		*/
		regression_t*	result)				/* Resultado da regressao		*/
{
	static unsigned int i,j,k,d,e,f,g,sum;
	static int** transposed_mat;
	static int** coefficient_mat;
	static int* indepenterms_vec;
	static int* solutioninf_vec;

	if(var_quantity > 1 && (var_quantity + 1) != par_quantity ){
		errorcondit++;
		return;
	}

	errorcondit = 0;
	indepenterms_vec = calloc(par_quantity,sizeof(int));
	solutioninf_vec = calloc(par_quantity,sizeof(int));
	coefficient_mat = calloc(par_quantity,sizeof(int*));
	transposed_mat = calloc(par_quantity,sizeof(int*));
	for(i = 0; i < par_quantity; i++){
		coefficient_mat[i] = calloc(par_quantity,sizeof(int));
		transposed_mat[i] = calloc(par_quantity,sizeof(int));
	}

	for(i = 0; i < quantity; i++){
		for(j = var_quantity + 1; j > 2; j--)
			variables[i][j] = variables[i][j-1];
		variables[i][0] = 0;
	}
	/* Se regressao polinomial, entao gera potencias de x */
	if(var_quantity == 1 && par_quantity > 2){
		for(j = 2; j < par_quantity - 1; j++){
			for(i = 0; i < quantity; i++)
				/* Truncamento na potencia entre variaveis temporariamente convertidas */
				variables[i][j + 1] = (int) pow((double) variables[i][2],(double) j);
		}
	}
	/* Equacoes normais */
	for(i = 0; i < par_quantity; i++){
		for(j = 0; j < par_quantity; j++){
			sum = 0;
			for(k = 0; k < quantity; k++)
				sum += variables[k][i] * variables[k][j];
			coefficient_mat[i][j] = sum; /* Matriz dos coeficientes */
		}
		sum = 0;
		for(k = 0; k < quantity; k++)
			sum += variables[k][i] * responses[k];
		indepenterms_vec[i] = sum;
	}
	/* Execucao do algoritmo de Decomposicao de Cholesky */
	cholesky(par_quantity,coefficient_mat);
	/* Execucao do algoritmo de Substituicoes Sucessivas */
	successive_subs(par_quantity,coefficient_mat,indepenterms_vec,solutioninf_vec);
	/* Transposicao de matrizes */
	for(i = 0; i < par_quantity; i++)
		for(j = 0; j < i; j++)
			transposed_mat[j][i] = coefficient_mat[i][j];
	/* Obtencao dos coeficientes por meio de Substituicoes Retroativas */
	retroactiv_subs(par_quantity,transposed_mat,solutioninf_vec,result->reg_coefficient);
	for(i = 0; i < quantity; i++){
		for(j = 0; j < par_quantity; j++)
			g += result->reg_coefficient[j] * variables[i][j];
		d = responses[i] - g;
		/* Truncamento em potencia de valores temporariamente convertidos */
		e += pow((double) d,2.0);
		f += pow((double) responses[i],2.0);
	}
	/* Calculo do coeficiente de determinacao */
	result->det_coefficient = 1 - e / (f - pow((double) indepenterms_vec[1],2.0) / quantity);
	result->sigma = e / (quantity - par_quantity); /* Variancia residual */
	for(i = 0; i < par_quantity; i++){
		free(coefficient_mat[i]);
		free(transposed_mat[i]);
	}
	free(indepenterms_vec);
	free(solutioninf_vec);
	free(coefficient_mat);
	free(transposed_mat);
}
