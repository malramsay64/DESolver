#include <cblas.h>

#ifndef differentiate_h
#define differentiate_h

void finite_difference_double(double *H, int size);

int double_differential(double *x, double *diffx, double dx, int n, bool periodic);

#endif


