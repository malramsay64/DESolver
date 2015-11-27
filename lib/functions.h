//
// Created by malcolm on 3/11/15.
//
#include <iostream>
#include <math.h>

#ifndef SHEAR_FUNCTIONS_H
#define SHEAR_FUNCTIONS_H

double mean(double *x, int size);
double variance(double *x, int size);
double stdev(double *x, int size);
double sum(double *x, int size);
void initialise( double *x, int size);
int mode(int *x, int size);

class stats{
    long long n;
    double M1,M2,M3,M4;
public:
    stats();
    void push(double val);
    double getMean();
    double getVariance();
    double getStandardDeviation();
    double getSkewness();
    double getKurtosis();
    long long numVals();
};

#endif //SHEAR_FUNCTIONS_H
