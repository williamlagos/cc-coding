#ifndef SIMPLE_H_
#define SIMPLE_H_

#define FLOOR(x) floor((x) * 100) / 100

int change(double value, double* coins);
int change_rec(double value, double* coins, int count);

#endif