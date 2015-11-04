//
// Created by malcolm on 4/11/15.
//

#include "output.h"
using namespace std;

int print(double *x, int size, double time, double dx, bool reset){
    ofstream outfile;
    if (reset){
        outfile.open("output.dat");
    }
    else {
        outfile.open("output.dat", ios::app);
    }
    outfile << "Timestep    " << time << endl;
    for (int i=0; i<size; i++){
        outfile << dx*i << " " << x[i] << endl;
    }
    outfile << endl;
    return 0;
}