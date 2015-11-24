//
// Created by malcolm on 4/11/15.
//

#include "output.h"
using namespace std;

int print(double *x, int size, double time, double dx, const char* fname, bool reset){
    ofstream outfile;
    if (reset){
        outfile.open(fname);
    }
    else {
        outfile.open(fname, ios::app);
    }
    for (int i=0; i<size; i++){
        outfile << dx*i << " " << x[i] << " " << time << endl;
    }
    outfile << endl;
    return 0;
}

