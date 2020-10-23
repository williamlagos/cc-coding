#include<stdio.h>
#include "recursive.h"

void recursive()
{
	int value = fibonacci(10);
	fprintf(stdout, "Fibonacci number in 10: %d\n", value);
}