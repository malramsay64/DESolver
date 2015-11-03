#include "noise.h"

std::normal_distribution<double> distribution(0, 1);
std::default_random_engine generator;

int noise(double *n, int size, double Q){
    for (int i=0; i<size; i++){
        n[i]=distribution(generator)*Q;
    }
    return 0;
}

double noise(double Q){
    return distribution(generator)*Q;
}

