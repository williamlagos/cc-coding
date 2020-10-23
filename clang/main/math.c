#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "main.h"
#include "calc.h"
#include "adjusts.h"
#include "equations.h"
#include "interpols.h"

void random_matrix(int** matrix)
{
	fprintf(stdout, "Gerando matriz randomica:\n");
	static int i, j;
	static int maxx = ORDER;
	static int maxy = ORDER;
	for (i = 0; i < maxx; i++){
		matrix[i] = (int*)malloc(maxy * sizeof(int));
		fprintf(stdout, "[");
		for (j = 0; j < maxy; j++){
			matrix[i][j] = rand() % RNDFACT + 1;
			if (j < maxy - 1) fprintf(stdout, "%d,", matrix[i][j]);
			else fprintf(stdout, "%d", matrix[i][j]);
		}
		fprintf(stdout, "]\n");
	}
}

int linears(int argc, char** argv)
{
	/* Código desativado, codigos de Gauss-Jacobi e Gauss-Seidel estao faltando */
	/* iterations = 10;
	static unsigned int i;
	static int max = ORDER;
	static int tolerance = 5;
	static int** matrix1 = NULL;
	static int** matrix2 = NULL;

	matrix1 = (int**)malloc(max * sizeof(int*));
	matrix2 = (int**)malloc(max * sizeof(int*));
	random_matrix(matrix1);
	random_matrix(matrix2);

	static int vector1[ORDER] = { 5, 8, 2, 3, 1 };
	static int vector2[ORDER] = { 5, 8, 2, 3, 1 };

	gauss_jacobi(ORDER, matrix1, vector1, tolerance, iterations);
	fprintf(stdout, "Erro condicional de Gauss-Jacobi: %d\n", errorconds);
	gauss_seidel(ORDER, matrix2, vector2, tolerance, iterations);
	fprintf(stdout, "Erro condicional de Gauss-Seidel: %d\n", errorconds);

	for (i = 0; i < max; i++) free(matrix1[i]);
	for (i = 0; i < max; i++) free(matrix2[i]);
	free(matrix1);
	free(matrix2);*/
	return EXIT_SUCCESS;
}

int adjusts(int argc, char** argv)
{
	int* responses;
	int** variables;
	regression_t result;
	unsigned int i, j, max, quantity, var_quantity, par_quantity;

	quantity = 10;
	var_quantity = 5;
	par_quantity = 5;
	max = par_quantity;
	result.det_coefficient = 0.0;
	result.sigma = 0.0;
	result.reg_coefficient = calloc(max, sizeof(int));

	responses = calloc(max, sizeof(int));
	variables = calloc(max, sizeof(int*));
	for (i = 0; i < max; i++){
		responses[i] = rand() % RAND_FACTOR;
		variables[i] = calloc(max, sizeof(int));
		for (j = 0; j < max; j++)
			variables[i][j] = rand() % RAND_FACTOR;
	}

	fprintf(stdout, "Comecando Regressao Linear...\n");
	regression(quantity, var_quantity, par_quantity, variables, responses, &result);
	fprintf(stdout, "Resultados:\nCoeficiente de determinacao: %f \n", result.det_coefficient);
	fprintf(stdout, "Variancia residual: %f\n\nCoeficientes de regressao:\n", result.sigma);
	for (i = 0; i < max; i++)
		fprintf(stdout, "%d: %d\n", i, result.reg_coefficient[i]);

	for (i = 0; i < max; i++)
		free(variables[i]);
	free(variables);
	free(responses);
	free(result.reg_coefficient);
	return EXIT_SUCCESS;
}

int equations(int argc, char** argv)
{
	int initial, inf_limit, sup_limit, eq_grade;
	unsigned int tolerance, itermax;
	int eq_vector[5] = { 5, 4, 3, 2, 1 };
	solution_t rregula_falsi, rbisection, rsecant, rnewton;

	initial = 2;
	eq_grade = 5;
	inf_limit = 0;
	sup_limit = 10;
	tolerance = itermax = 10;

	fprintf(stdout, "Resolvendo algumas equacoes...\n");
	rregula_falsi = regula_falsi(inf_limit, sup_limit, tolerance, itermax, eq_vector, eq_grade);
	rbisection = bisection(inf_limit, sup_limit, tolerance, itermax, eq_vector, eq_grade);
	rsecant = secant(inf_limit, sup_limit, tolerance, itermax, eq_vector, eq_grade);
	rnewton = newton(initial, tolerance, itermax, eq_vector, eq_grade);

	fprintf(stdout, "Regula Falsi:\nIteracoes: %d\nRaiz: %f\n", rregula_falsi.iterations, rregula_falsi.root);
	fprintf(stdout, "Bissecao:\nIteracoes: %d\nRaiz: %f\n", rbisection.iterations, rbisection.root);
	fprintf(stdout, "Secante:\nIteracoes: %d\nRaiz: %f\n", rsecant.iterations, rsecant.root);
	fprintf(stdout, "Newton:\nIteracoes: %d\nRaiz: %f\n", rnewton.iterations, rnewton.root);

	return EXIT_SUCCESS;
}

int interpols(int argc, char** argv)
{
	static unsigned int i, max, number, value, rnewton, rlagrange;
	static int xcoords[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	static int ycoords[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	static int values[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	static int* s;

	s = calloc(max, sizeof(int));
	value = number = 5;

	fprintf(stdout, "Calculating interpolations...\n");
	rlagrange = lagrange(max, xcoords, ycoords, value);
	rnewton = interpol_newton(max, xcoords, ycoords, value);
	spline(number, xcoords, ycoords, max, values, s);

	fprintf(stdout, "Resultado da Interpolacao de Lagrange: %d\n", rlagrange);
	fprintf(stdout, "Resultado da Interpolacao de Newton: %d\n", rnewton);
	fprintf(stdout, "Resultado da Interpolacao de Spline Cubica:\n");
	for (i = 0; i < max; i++)
		fprintf(stdout, "%d", s[i]);

	free(s);

	return EXIT_SUCCESS;
}
