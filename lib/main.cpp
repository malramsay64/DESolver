#include <string>
#include <iostream>
#include "noise.h"
#include "integrator.h"


using namespace std;

int main (int argc, char** argv){
    double a[100];
    
    for (int i=0; i<100; i++){
        a[i] = 0;
    }

    integrator(a, 100, 0.01, 1);
    for (int i=0; i<10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << a[i * 10 + j];
        }
        cout << endl;
    }
    return 0;
}

