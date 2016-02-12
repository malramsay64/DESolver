//
// Created by malcolm on 4/12/15.
//

#include "Integrator.h"
#include "Equation.h"

void Numerical_Integrator::reset(){
    x = std::valarray<double>(0.,size);
    curr_step = 0;
}

void Numerical_Integrator::print() const {
    std::ofstream outfile{fname, std::ios::app};
    double dx = 1./x.size();
    for(int i=0;i<x.size(); i++){
        outfile << i*dx << " "  << std::setprecision(5) << x[i] << " " << timestep*curr_step << std::endl;
    }
    outfile.close();
}

void Numerical_Integrator::integrate(Shear & n) {
    std::ofstream header{fname};
    header << "Xpos Height Time" << std::endl;
    header.close();
    while (timestep * curr_step++ < total_time) {
        step(n);
    }
}

std::ostream &operator<<(std::ostream &os, const Numerical_Integrator &n) {
    return os << n.getSize() << " " << n.getTotalTime() << " " << n.getTimestep() \
            << " " << n.getCharVal();
}


void Euler::integrate(Shear & n) {
    std::ofstream header{fname};
    header << "Xpos Height Time" << std::endl;
    header.close();
    while (timestep * curr_step < total_time) {
        step(n);
    }
}

void Euler::integrate(NDEquation & n) {
    std::ofstream header{fname};
    header << "Xpos Height Time" << std::endl;
    header.close();
    while (timestep * curr_step++ < total_time) {
        step(n);
    }
}

void Euler::step(Shear &e) {
    ++curr_step;
    x += e.increment(x, timestep);
    if (curr_step % print_freq == 0){
        print();
    }
}

void Euler::step(NDEquation &e) {
    ++curr_step;
    x += e.increment(x, timestep);
    if (curr_step % print_freq == 0){
        print();
    }
}

double Euler::getCharVal() const {
    Stats::Stats s{};
    for (auto i=0; i<x.size(); i++){
        s.push(x[i]);
    }
    return s.getMean();
}

std::ostream &operator<<(std::ostream &os, const Euler &n) {
    return os << n.getSize() << " " << n.getTotalTime() << " " << n.getTimestep() \
            << " " << n.getCharVal();
}

