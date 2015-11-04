#include "integrator.h"

double total_time = 0.001;

using namespace std;

double timestep(double dx, double q){
    if (q != 0) {
        return fabs(0.01 * (dx * dx) / (4 * q));
    }
    else {
        return 1e-3;
    }
}

void integrator(double *x, int size, double dx, double total_time, double Q) {
    double time = 0;
    double dt = timestep(dx,Q);
    double *H, *n;
    int step = 0;
    int print_every = int((total_time/dt)/1000);
    H = (double *) malloc(size * size * sizeof(double));
    n = (double *) malloc(size * sizeof(double));
    finite_difference_double(H,size);
    cout << "Timesteps: " << total_time/dt << " Size x: " << size << endl;
    print(x, size, time, dx, true);
    while (time < total_time){
        noise(n, size, Q);
        cblas_dgemv(CblasRowMajor,CblasNoTrans, size, size, dt, H, size, x, 1, 1, x, 1);
        cblas_daxpy(size,dt,n,1,x,1);
        time += dt;
        step++;
        if (step % print_every == 0){
            print(x, size, time, dx);
            cout << step << " of " << int(total_time/dt) << endl;

        }
    }
    free(H);
    free(n);
}


