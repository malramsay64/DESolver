//
// Created by malcolm on 3/11/15.
//

#include "functions.h"


double mean(double *x, int size){
    double res = 0;
    for (int i=0; i<size; i++){
        res = res + (x[i]-res)/(i+1);
    }
    return res;
}

double variance(double *x, int size){
    double mean = 0;
    double M2 = 0;
    double delta;
    for (int i=0; i<size; i++){
        delta = x[i] - mean;
        mean = mean + delta/(i+1.);
        M2 = M2 + delta*(x[i]-mean);
    }
    if (size < 2){
        return NAN;
    }
    else {
        return M2/(size-1.);
    }

}

double stdev(double *x, int size){
    return sqrt(variance(x,size));
}

double sum(double *x, int size){
    double res = 0;
    for (int i=0; i<size; i++){
        res += x[i];
    }
    return res;
}