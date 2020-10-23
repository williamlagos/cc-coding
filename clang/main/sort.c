#include<stdio.h>
#include<stdlib.h>
#include "sort.h"

int 
compare(
	const void * a,
	const void * b)
{
	return (*(int*)a - *(int*)b);
}

void sort()
{
	static unsigned int i;
	int list[10] = { 0, 4, 8, 1, 3, 5, 7, 9, 2, 6 };
	int qlst[10] = { 6, 3, 1, 8, 7, 2, 5, 0, 4, 9 };
	fprintf(stdout, "[");
	for (i = 0; i < 9; i++)
		fprintf(stdout, "%d,", list[i]);
	fprintf(stdout, "%d]\n", list[i]);
	heapsort(list, 10);
	fprintf(stdout, "Sorted array with heapsort: [");
	for (i = 0; i < 9; i++)
		fprintf(stdout, "%d,", list[i]);
	fprintf(stdout, "%d]\n", list[i]);

	fprintf(stdout, "[");
	for (i = 0; i < 9; i++)
		fprintf(stdout, "%d,", qlst[i]);
	fprintf(stdout, "%d]\n", qlst[i]);
	qsort(qlst, 10, sizeof(int), compare);
	fprintf(stdout, "Sorted array with quicksort: [");
	for (i = 0; i < 9; i++)
		fprintf(stdout, "%d,", qlst[i]);
	fprintf(stdout, "%d]\n", qlst[i]);
}