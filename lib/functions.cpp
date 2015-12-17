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

Stats::Stats(){
    M1 = M2 = M3 = M4 = 0.0;
    n=0;
}

Stats::Stats(const std::valarray<double> &x){
    M1=M2=M3=M4=0.0;
    n=0;
    for (size_t i = 0; i != x.size(); i++){
        push(x[i]);
    }
}

void Stats::push(double val) {
    double delta, delta_n, delta_n2, term1;
    long long n1 = n;
    n++;
    delta = val - M1;
    delta_n = delta/n;
    delta_n2 = delta_n * delta_n;
    term1 = delta * delta_n * n1;
    M1 += delta_n;
    M4 += term1 * delta_n2 * (n*n - 3*n + 3) + 6 * delta_n2 * M2 - 4 * delta_n * M3;
    M3 += term1 * delta_n * (n-2)-3*delta_n * M2;
    M2 += term1;
}

double Stats::getMean() {
    return M1;
}

double Stats::getVariance() {
    return M2/(n-1.0);
}
double Stats::getStandardDeviation(){
    return sqrt(getVariance());
}
double Stats::getSkewness(){
    return sqrt(double(n))*M3/pow(M2,1.5);
}
double Stats::getKurtosis() {
    return double(n)*M4/(M2*M2)-3.0;
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

void initialise(double * a, int size){
    for (int i=0; i<size; i++){
        a[i] = 0;
    }
}

int mode(int *a, int size){
    if (size == 3){
        if (a[0] == a[1] || a[0] == a[2]){
            return a[0];
        }
        else if (a[1] == a[2]){
            return a[1];
        }
        return 2;
    }
    return 0;
}