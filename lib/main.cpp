#include <string>
#include <iostream>
#include "noise.h"
#include "integrator.h"


using namespace std;

int main (int argc, const char* argv[]){
    double a[100], b[100], c[100];
    
    for (int i=0; i<100; i++){
        a[i] = 0;
        b[i] = 0;
    }
    integrator(a, 100, 0.01);
    for (int i=0; i<100; i++){
        cout << a[i] << endl;
    }
}

