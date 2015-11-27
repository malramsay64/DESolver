
#ifndef differentiate_h
#define differentiate_h

void finite_difference_double_matrix(double *H, int size);
double finite_difference_double(double *H, int size, double dx, int index);

int double_differential(double *x, double *diffx, double dx, int n, bool periodic);

#endif


