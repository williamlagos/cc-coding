/*
 * equations.h
 *
 *  Created on: 16/06/2014
 *      Author: william
 */

#ifndef EQUATIONS_H_
#define EQUATIONS_H_

typedef struct{
	double root;
	unsigned int iterations;
	unsigned int errorconds;
} solution_t;

solution_t regula_falsi(int inf_limit,int sup_limit,unsigned int tolerance,unsigned int itermax,int* eq_vector,int eq_grade);
solution_t bisection(int inf_limit,int sup_limit,unsigned int tolerance,unsigned int itermax,int* eq_vector,int eq_grade);
solution_t secant(int inf_limit,int sup_limit,unsigned int tolerance,unsigned int itermax,int* eq_vector,int eq_grade);
solution_t newton(int initial,unsigned int tolerance,unsigned int itermax,int* eq_vector,int eq_grade);

#define POW(X,Y) (int) pow((double) X, (double) Y)
#define FOREVER while(1)

#endif /* EQUATIONS_H_ */
