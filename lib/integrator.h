#include <iostream>
#include <sstream>
#include "noise.h"
#include "differentiate.h"
#include "output.h"
#include "input.h"

#ifndef integrator_h
#define integrator_h

double timestep(double dx, double q);
void integrator(double *x, variables v);

#endif
