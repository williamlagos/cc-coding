/* 														*
 * Calculate - program to calculate linear systems by	*
 * iterative methods like Gauss-Jacobi and Gauss-Seidel *
 * 														*
 * William Oliveira de Lagos <william.lagos1@gmail.com> *
 *														*/

#ifndef CALC_H
#define CALC_H

#define FOREVER while(1)
#define ORDER 5
#define RNDFACT 8

static int iterations;
static int errorconds;

void random_matrix(int** matrix);
void gauss_jacobi(int max,int** matrix,int* vector,int tolerance,int itermax);
void gauss_seidel(int max,int** matrix,int* vector,int tolerance,int itermax);

#endif
