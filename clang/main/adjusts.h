/*
 * adjusts.h
 *
 *  Created on: 16/06/2014
 *      Author: william
 */

#ifndef ADJUSTS_H_
#define ADJUSTS_H_

#define RAND_FACTOR 9

typedef struct{
	int* reg_coefficient;
	double det_coefficient;
	double sigma;
} regression_t;

int cholesky(int order,int** matrix);
void successive_subs(int order,int** matrix,int* vector,int* solution);
void retroactiv_subs(int order,int** matrix,int* vector,int* solution);
void regression(unsigned int quantity,unsigned int var_quantity,unsigned int par_quantity,int** variables,int* responses,regression_t* result);

static unsigned int errorcondit;

#endif /* ADJUSTS_H_ */
