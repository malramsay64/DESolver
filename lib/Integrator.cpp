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

Numerical_Integrator::~Numerical_Integrator() {
    outfile.close();
}

Numerical_Integrator::Numerical_Integrator(NDEquation e, size_t s, double time, double dt) {
    eq = e;
    size = s;
    x = std::valarray<double>(0., s);
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = ceill(total_time / timestep);
}

Numerical_Integrator::Numerical_Integrator(NDEquation e,size_t s, double time, double dt, int num_print) {
    eq = e;
    size = s;
    x = std::valarray<double>(0., s);
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = floorl(total_time/timestep)/num_print;
    outfile.open("outfile.dat");
}

Numerical_Integrator::Numerical_Integrator(NDEquation e, size_t s, double time, double dt, int num_print, std::string fname) {
    eq = e;
    size = s;
    x = std::valarray<double>(0., s);
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = floorl(total_time/timestep)/num_print;
    outfile.open(fname.c_str());
}

/*
Numerical_Integrator::Numerical_Integrator(const Numerical_Integrator& ni) {
    eq = ni.eq;
    size = ni.size;
    x = std::valarray{ni.x};
    total_time = ni.total_time;
    curr_step = ni.curr_step;
    print_freq = ni.print_freq;
    outfile = make_fname(;
}
*/

void Numerical_Integrator::print() {
    for(int i=0;i<x.size(); i++){
        outfile << std::fixed << std::setprecision(5) << x[i] << ' ' << std::endl;
    }
}

void Numerical_Integrator::step() {
}

void Numerical_Integrator::integrate() {
    while (timestep * curr_step++ < total_time) {
        step();
    }
}

NDEquation &Numerical_Integrator::getEquation() {
    return eq;
}

size_t Numerical_Integrator::getSize() const {
    return size;
}

std::valarray<double> &Numerical_Integrator::getX() {
    return x;
}

double Numerical_Integrator::getTotalTime() const {
    return total_time;
}

int Numerical_Integrator::getCurrStep() const {
    return curr_step;
}

double Numerical_Integrator::getTimestep() const {
    return timestep;
}

long Numerical_Integrator::getPrintFreq() const {
    return print_freq;
}

std::ofstream &Numerical_Integrator::getOutfile() {
    return outfile;
}

std::ostream &operator<<(std::ostream &os, const Numerical_Integrator &n) {
    return os << n.eq << ' ' << n.getSize() << ' ' << n.getTotalTime() << ' ' << n.getCurrStep()\
 << ' ' << n.getTimestep() << ' ' << n.getPrintFreq();
}

Euler::Euler(const variables &v) {
    eq = Shear{v.A, v.delta, v.Q};
    size = v.size;
    x = std::valarray<double>(0., v.size);
    total_time = v.total_time;
    curr_step = 0;
    timestep = v.dt;
    print_freq = v.print ? floorl(total_time / timestep) / 100 : ceill(total_time / timestep);
    outfile.open(make_fname(v));
}

void Euler::step() {
    x += move(eq.increment(x, timestep));
    ++curr_step;
    if (curr_step % print_freq == 0){
        print();
    }
}
/*
std::ostream& operator<<(std::ostream& os, const Numerical_Integrator& n){
    return os << n.getEquation() << " " << n.getSize() << " " << n.getTotalTime() << " " << n.getCurrStep()\
            << " " << n.getTimestep() << " " << n.getPrintFreq();
}
 */
