#include <iostream>
#include "noise.h"
#include "differentiate.h"
#include "output.h"

#ifndef integrator_h
#define integrator_h

double timestep(double dx, double q);
void integrator_cblas(double *x, int size, double dx, double dt, double total_time, double Q, double A=0, double delta=0);
void integrator(double *x, int size, double dx, double dt, double total_time, double Q, double A=0, double delta=0);

#endif
