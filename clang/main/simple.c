#include<stdio.h>
#include<stdlib.h>
#include "simple.h"
#include "main.h"

void simple()
{
	fprintf(stdout, "Counting a change for R$ 2.75\n");
	static double coins[6] = { 0.50, 0.25, 0.10, 0.05, 0.01 };
	int number = change(2.75, coins);
	fprintf(stdout, "Number of coins exchanged: %d\n", number);
}

