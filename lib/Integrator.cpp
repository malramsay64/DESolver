//
// Created by malcolm on 4/12/15.
//

#include "Integrator.h"


Numerical_Integrator::Numerical_Integrator() {
    size = 0;
    total_time = 0;
    curr_step = 0;
    timestep = 0;
    print_freq = 0;
}

Numerical_Integrator::Numerical_Integrator(NDEquation e, size_t s, double time, double dt) {
    eq = e;
    size = s;
    x = std::valarray<double>{s,0};
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = 0;
}

Numerical_Integrator::Numerical_Integrator(NDEquation e,size_t s, double time, double dt, int num_print) {
    eq = e;
    size = s;
    x = std::valarray<double>{s,0};
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = floorl(total_time/timestep)/num_print;
    outfile.open("outfile.dat");
}

Numerical_Integrator::Numerical_Integrator(NDEquation e, size_t s, double time, double dt, int num_print, std::string fname) {
    eq = e;
    size = s;
    x = std::valarray<double>{s,0};
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = floorl(total_time/timestep)/num_print;
    outfile.open(fname.c_str());
}

void Numerical_Integrator::print() {
    for(int i=0;i<x.size(); i++){
        outfile << x[i] << std::endl;

    }
}

void Euler::step() {
    x += eq.increment(x, timestep);
    ++curr_step;
    if (curr_step % print_freq == 0){
        print();
    }
}