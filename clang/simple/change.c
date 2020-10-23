#include<stdio.h>
#include<math.h>
#include "simple.h"

int 
change(double value, double* coins)
{
	return change_rec(value, coins, 0);
}

int
change_rec(double value, double* coins, int count)
{
	static double remainder,precise_sum;
	unsigned int num_coins;
	num_coins = (int) FLOOR(value / coins[count]);
	remainder = value - (num_coins * coins[count]);
	fprintf(stdout, "%d coins of %.2f\n", num_coins, coins[count]);
	if (remainder != 0.0){
		count++;
		return num_coins + change_rec(remainder,coins,count);
	}else{
		return num_coins;
	}
}