//
// Created by malcolm on 3/11/15.
//
#include <iostream>
#include <cmath>
#include <valarray>

#ifndef SHEAR_FUNCTIONS_H
#define SHEAR_FUNCTIONS_H

double mean(double *x, int size);
double variance(double *x, int size);
double stdev(double *x, int size);
double sum(double *x, int size);
void initialise( double *x, int size);
int mode(int *x, int size);

class Stats{
    long long n;
    double M1,M2,M3,M4;
public:
    Stats();
    Stats(const std::valarray<double>&);
    void push(double val);
    double getMean();
    double getVariance();
    double getStandardDeviation();
    double getSkewness();
    double getKurtosis();
    long long numVals();
};

template <class T>
T accumulate (const std::valarray<T>& v,  T init){
    for (size_t i = 0; i != v.size(); i++) {
        init += v[i];
    }
    return init;
}

template <class T>
T accumulate (const std::valarray<T>& v){
    T init{};
    for (size_t i = 0; i != v.size(); i++) {
        init += v[i];
    }
    return init;
}

#endif //SHEAR_FUNCTIONS_H
