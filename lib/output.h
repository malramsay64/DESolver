//
// Created by malcolm on 4/11/15.
//
#include <iostream>
#include <fstream>
#include <string.h>
#include "Integrator.h"

#ifndef SHEAR_OUTPUT_H
#define SHEAR_OUTPUT_H

int print(double *x, int size, double time, double dx, const char *fname="output.dat", bool reset=false);


#endif //SHEAR_OUTPUT_H
