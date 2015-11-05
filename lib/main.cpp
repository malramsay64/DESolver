#include <string>
#include <iostream>
#include <getopt.h>
#include "integrator.h"


using namespace std;

// Global variables

void useage(){
   cout << \
           "Input variables\n"
           "    -s  size\n"
           "        The number of x values\n"
           "    -q  Q\n"
           "        The stdev of the random number generator\n"
           "    -t  total time\n"
           "        The total runtime of the simulation\n"
           "    -a  A\n"
           "        The magnitude of the shear force\n"
           "    -x  dx\n"
           "        The size of the steps in x\n"
           "    -d  delta\n"
           "        The temperature of the system\n"
           "    -f   dt\n"
           "        The size of each timestep\n" << endl;
}

int main (int argc, char** argv){
    // Arguments
    int size = 100;
    double Q = 1;
    double total_time = 0.001;
    double A = 0;
    double dx = 0;
    double delta = 0;
    double dt = 0;
    int opt;
    while ((opt = getopt(argc, argv, "s:q:t:a:x:d:f:h")) != -1){
        switch (opt) {
            case 's':
                size = atoi(optarg);
                break;
            case 'q':
                Q = atof(optarg);
                break;
            case 't':
                total_time = atof(optarg);
                break;
            case 'a':
                A = atof(optarg);
                break;
            case 'x':
                dx = atof(optarg);
                break;
            case 'd':
                delta = atof(optarg);
                break;
            case 'f':
                dt = atof(optarg);
                break;
            case 'h':
                useage();
                return 0;
            case '?':
                if (optopt == 's' || optopt == 'Q') {
                    cerr << "Option -" << toascii(optopt) << " requires an argument." << endl;
                }
                else {
                    cerr << "Unknown option -" << toascii(optopt) << endl;
                }
                return 1;
            default:
                abort();
        }
    }
    if (dx == 0){
        dx = 1./size;
    }
    if (dt == 0){
        dt = timestep(dx, size);
    }
    double *a = (double *) malloc(size*sizeof(double));
    for (int i=0; i<size; i++){
        a[i] = 0;
    }

    integrator(a, size, dx, dt, total_time, Q, A, delta);

    free(a);
    return 0;
}

