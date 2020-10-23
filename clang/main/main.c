/* 														*
* Calculate - program to calculate linear systems by	*
* iterative methods like Gauss-Jacobi and Gauss-Seidel *
* 														*
* William Oliveira de Lagos <william.lagos1@gmail.com> *
*														*/

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "main.h"

void main(int argc, char** argv)
{
	/*linears(argc, argv);
	  equations(argc, argv);
	  adjusts(argc, argv);
	  interpols(argc, argv);*/
	sort();
	simple();
	recursive();
	fprintf(stdout, "Finish of algorithms test.\n");
	int keypress = getchar();
	exit(EXIT_SUCCESS);
}