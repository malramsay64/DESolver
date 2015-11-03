#include "integrator.h"

double total_time = 0.001;
double Q = 1;

using namespace std;

double timestep(double dx, double q){
    return 0.001*(dx*dx)/(4*q);
}

void integrator(double *x, int size, double dx) {
    double time = 0;
    double dt = timestep(dx,Q);
    double *H, *n;
    H = (double *) malloc(size * size * sizeof(double));
    n = (double *) malloc(size * sizeof(double));
    finite_difference_double(H,size);
    cout << "Timesteps: " << total_time/dt << " Size x: " << size << endl;
    while (time < total_time){
        noise(n, size, Q);
        cblas_dgemv(CblasRowMajor,CblasNoTrans, size, size, dt, H, size, x, 1, 1, x, 1);
        cblas_daxpy(size,dt,n,1,x,1);
        time += dt;
    }
}


