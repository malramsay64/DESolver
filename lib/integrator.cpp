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

void integrator(double x, variables v){
    double time = 0;
    int step = 0;
    int print_every = int((v.total_time/v.dt)/100)+1;
    valarray<double> dH(v.size);
    double *dH = (double *)malloc(v.size*sizeof(double));
    stringstream fname;
    string tmp;
    fname << v.total_time << "-" << v.dt << "-" << v.size << "-" << v.Q << "-" << v.A << "-" << v.delta << ".dat";
    tmp = fname.str();
    if (v.print){
        print(x, v.size, time, v.dx, tmp.c_str(), true);
    }
    Noise noise{v.Q/sqrt(v.dt/(v.dx*v.dx))};
    while (time < v.total_time) {
        for (int i = 0; i < v.size; i++) {
            dH[i] = finite_difference_double(x, v.size, v.dx, i);
            if (dH[i] < 0) {
                dH[i] += v.A * dH[i];
            }
            d[H] +=
            if (step % v.delay == 0) {
                dH[i] += noise.getVal();
            }
            dH[i] *= v.dt;
        }
        for (int i = 0; i < v.size; i++) {
            x[i] += dH[i];
        }
        time += v.dt;
        step++;
        if (v.print && step % print_every == 0) {
            print(x, v.size, time, v.dx, tmp.c_str());
        }
    }
    free(dH);
}


