#include <string>
#include <iostream>
#include "noise.h"
#include "integrator.h"
#include "output.h"


using namespace std;

// Global variables
int size;
double totalTime;
double Q;


int main (int argc, char** argv){
    size = 1000;
    Q = 1;
    double a[size];
    
    for (int i=0; i<size; i++){
        a[i] = 0;
    }

    integrator(a, size, 0.01, 1, Q);
    return 0;
}

