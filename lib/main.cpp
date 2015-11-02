#include <string>
#include <iostream>
#include "noise.h"
#include "differentiate.h"

using namespace std;

int main (int argc, const char* argv[]){
    cout << "Hello World" << endl;
    double a[100], b[100], c[100];
    
    for (int i=0; i<100; i++){
        a[i] = 0;
        b[i] = 0;
    }
    for (int j=0; j<10; j++){
        double_differential(a, b, 1./100, 100, true); 
        for (int i=0; i<100; i++){
            a[i] = 0.001*(b[i]+noise(0.00001));
            cout << a[i] << " " << b[i] << ",";
        }
        cout << endl;
    }
    for (int i=0; i<100; i++){
        cout << a[i] << endl;
    }
}

