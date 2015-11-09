#include "integrator.h"
#include "input.h"

using namespace std;

double timestep(double dx, double q){
    if (q != 0) {
        return fabs(0.01*(dx * dx) / (4 * q));
    }
    else {
        return 1e-3;
    }
}

void integrator(double *x, variables v){
    double time = 0;
    int step = 0;
    int print_every = int((v.total_time/v.dt)/20)+1;
    double *dH = (double *)malloc(v.size*sizeof(double));
    //cout << "Timesteps: " << total_time/dt << " Size x: " << size << endl;
    stringstream fname;
    string tmp;
    fname << v.total_time << "-" << v.dt << "-" << v.size << "-" << v.Q << "-" << v.A << "-" << v.delta << ".dat";
    tmp = fname.str();
    print(x, v.size, time, v.dx, tmp.c_str(), true);
    while (time < v.total_time) {

        if (v.A == 0){
            if (step % v.delay == 0) {
                // Noise added
                for (int i = 0; i < v.size; i++) {
                    dH[i] = v.dt * (finite_difference_double(x, v.size, v.dx, i) + noise(v.Q));
                }
            }
            else {
                // No noise added to simulation
                for (int i = 0; i < v.size; i++) {
                    dH[i] = v.dt * (finite_difference_double(x, v.size, v.dx, i));
                }
            }
            for (int i=0; i<v.size; i++){
                x[i] += dH[i];
            }
        }
        else {
            for (int i=0; i<v.size; i++){
                dH[i] = finite_difference_double(x, v.size, v.dx, i);
                if (dH[i] < 0){
                    dH[i] += v.delta + v.A*dH[i];
                }
                dH[i] += noise(v.Q);
                dH[i] *= v.dt;
            }
            for (int i=0; i<v.size; i++){
                x[i] += dH[i];
            }
        }

        time += v.dt;
        step++;
        if (step % print_every == 0) {
            print(x, v.size, time, v.dx, tmp.c_str());
        }
    }
    free(dH);
}


void integrator_cblas(double *x, variables v) {
    double time = 0;
    double *H, *n;
    int step = 0;
    int print_every = int((v.total_time/v.dt)/20)+1;
    double *dH = (double *)malloc(v.size*sizeof(double));
    H = (double *) malloc(v.size * v.size * sizeof(double));
    n = (double *) malloc(v.size * sizeof(double));
    finite_difference_double_matrix(H, v.size);
    //cout << "Timesteps: " << total_time/dt << " Size x: " << size << endl;
    char fname[30];
    sprintf(fname, "%f-%i-%f-%f.dat", v.total_time, v.size, v.Q, v.A);
    print(x, v.size, time, v.dx, fname, true);
    while (time < v.total_time){
        noise(n, v.size, v.Q);
        cblas_dgemv(CblasRowMajor,CblasNoTrans, v.size, v.size, v.dt/(v.dx*v.dx), H, v.size, x, 1, 1, x, 1);
        cblas_daxpy(v.size,v.dt,n,1,x,1);
        time += v.dt;
        step++;
        if (step % print_every == 0){
            print(x, v.size, time, v.dx, fname);
        }
    }
    free(H);
    free(n);
}


