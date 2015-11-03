#include <iostream>
#include "noise.h"
#include "differentiate.h"

#ifndef integrator_h
#define integrator_h

double timestep(double dx, double q);
void integrator(double *x, int size, double dx, double Q);

#endif
