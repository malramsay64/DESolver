#include "integrator.h"

double total_time = 0.0000001;
double Q = 1;

using namespace std;

double timestep(double dx, double q){
    return 0.001*(dx*dx)/(4*q);
}

void integrator(double *x, int size, double dx) {
    double time = 0;
    double dt = timestep(dx,Q);
    double *b;
    b = (double *) malloc(size * sizeof(double));
    cout << "Timesteps: " << total_time/dt << " Size x: " << size << endl;
    while (time < total_time){
        double_differential(x,b,dx,size,true);
        for (int i=0; i<size; i++){
            x[i] += dt*(b[i]+noise(Q));
        }
        time += dt;
    }
}


