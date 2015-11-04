#include <string>
#include <iostream>
#include "noise.h"
#include "integrator.h"
#include "output.h"


using namespace std;

// Global variables


int main (int argc, char** argv){
    int size;
    double Q;
    size = 100;
    Q = 1;
    double a[size];
    
    for (int i=0; i<size; i++){
        a[i] = 0;
    }
    integrator(a, size, 0.01, timestep(0.01, Q), 0.01, Q, 0.1);
    return 0;
}

