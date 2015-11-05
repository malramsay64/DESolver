#include "integrator.h"

using namespace std;

double timestep(double dx, double q){
    if (q != 0) {
        return fabs(0.01*(dx * dx) / (4 * q));
    }
    else {
        return 1e-3;
    }
}

void integrator(double *x, int size, double dx, double dt, double total_time, double Q, double A, double delta){
    double time = 0;
    int step = 0;
    int print_every = int((total_time/dt)/20)+1;
    double *dH = (double *)malloc(size*sizeof(double));
    cout << "Timesteps: " << total_time/dt << " Size x: " << size << endl;
    stringstream fname;
    string tmp;
    fname << total_time << "-" << dt << "-" << size << "-" << Q << "-" << A << "-" << delta << ".dat";
    tmp = fname.str();
    print(x, size, time, dx, tmp.c_str(), true);
    while (time < total_time) {
        if (A == 0){
            for (int i=0; i<size; i++){
                dH[i] = dt*(finite_difference_double(x, size, dx, i)+noise(Q));
            }
            for (int i=0; i<size; i++){
                x[i] += dH[i];
            }
        }
        else {
            for (int i=0; i<size; i++){
                dH[i] = finite_difference_double(x, size, dx, i);
                if (dH[i] < 0){
                    dH[i] += delta + A*dH[i];
                }
                dH[i] += noise(Q);
                dH[i] *= dt;
            }
            for (int i=0; i<size; i++){
                x[i] += dH[i];
            }
        }

        time += dt;
        step++;
        if (step % print_every == 0) {
            print(x, size, time, dx, tmp.c_str());
        }
    }
    free(dH);
}


void integrator_cblas(double *x, int size, double dx, double dt, double total_time, double Q, double A, double delta) {
    double time = 0;
    double *H, *n;
    int step = 0;
    int print_every = int((total_time/dt)/20)+1;
    double *dH = (double *)malloc(size*sizeof(double));
    H = (double *) malloc(size * size * sizeof(double));
    n = (double *) malloc(size * sizeof(double));
    finite_difference_double_matrix(H, size);
    cout << "Timesteps: " << total_time/dt << " Size x: " << size << endl;
    char fname[30];
    sprintf(fname, "%f-%i-%f-%f.dat", total_time, size, Q, A);
    print(x, size, time, dx, fname, true);
    while (time < total_time){
        noise(n, size, Q);
        cblas_dgemv(CblasRowMajor,CblasNoTrans, size, size, dt/(dx*dx), H, size, x, 1, 1, x, 1);
        cblas_daxpy(size,dt,n,1,x,1);
        time += dt;
        step++;
        if (step % print_every == 0){
            print(x, size, time, dx, fname);
        }
    }
    free(H);
    free(n);
}

