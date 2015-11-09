#include <iostream>
#include "noise.h"
#include "differentiate.h"
#include "output.h"
#include "input.h"

#ifndef integrator_h
#define integrator_h

double timestep(double dx, double q);
void integrator_cblas(double *x, variables v);
void integrator(double *x, variables v);

#endif
