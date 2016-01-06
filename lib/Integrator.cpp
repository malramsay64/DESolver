//
// Created by malcolm on 4/12/15.
//

#include "Integrator.h"
#include "Equation.h"


Numerical_Integrator::Numerical_Integrator() {
    size = 0;
    total_time = 0;
    curr_step = 0;
    timestep = 0;
    print_freq = 0;
    fname = "outfile.dat";
    std::ofstream header{fname};
    header << "Xpos Height Time" << std::endl;
    header.close();
}

Numerical_Integrator::~Numerical_Integrator() {
}

Numerical_Integrator::Numerical_Integrator(size_t s, double time, double dt) {
    size = s;
    x = std::valarray<double>(0., s);
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = ceill(total_time / timestep);
    fname = "outfile.dat";
    std::ofstream header{fname};
    header << "Xpos Height Time" << std::endl;
    header.close();
}

Numerical_Integrator::Numerical_Integrator(size_t s, double time, double dt, int num_print) {
    size = s;
    x = std::valarray<double>(0., s);
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = floorl(total_time/timestep)/num_print;
    fname = "outfile.dat";
    std::ofstream header{fname};
    header << "Xpos Height Time" << std::endl;
    header.close();
}

Numerical_Integrator::Numerical_Integrator(size_t s, double time, double dt, int num_print, std::string infname) {
    size = s;
    x = std::valarray<double>(0., s);
    total_time = time;
    curr_step = 0;
    timestep = dt;
    print_freq = floorl(total_time/timestep)/num_print;
    fname = infname;
    std::ofstream header{fname};
    header << "Xpos Height Time" << std::endl;
    header.close();
}

Numerical_Integrator::Numerical_Integrator(const Numerical_Integrator& ni) {
    size = ni.size;
    x = std::valarray<double>{ni.x};
    total_time = ni.total_time;
    curr_step = ni.curr_step;
    print_freq = ni.print_freq;
    fname = ni.fname;
}

Numerical_Integrator::Numerical_Integrator(Numerical_Integrator &&ni) {
    size = ni.size;
    x = std::move(ni.x);
    total_time = ni.total_time;
    curr_step = ni.curr_step;
    print_freq = ni.print_freq;
    fname = std::move(ni.fname);
}

void Numerical_Integrator::reset(){
    x = std::valarray<double>(0.,size);
    curr_step = 0;
    std::ofstream header{fname};
    header << "Xpos Height Time" << std::endl;
    header.close();
}

void Numerical_Integrator::print() const {
    std::ofstream outfile{fname, std::ios::app};
    double dx = 1./x.size();
    for(int i=0;i<x.size(); i++){
        outfile << i*dx << " " << std::scientific << std::setprecision(5) << x[i] << " " << timestep*curr_step << std::endl;
    }
    outfile.close();
}


void Numerical_Integrator::integrate(Shear & n) {
    while (timestep * curr_step++ < total_time) {
        step(n);
    }
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

double Numerical_Integrator::getCharVal() const {
    return 0;
}



std::ostream &operator<<(std::ostream &os, const Numerical_Integrator &n) {
    return os << n.getSize() << " " << n.getTotalTime() << " " << n.getTimestep() \
            << " " << n.getCharVal();
}

Euler::Euler(){
    variables v{};
    size = v.size;
    x = std::valarray<double>(0., v.size);
    total_time = v.total_time;
    curr_step = 0;
    timestep = v.dt;
    print_freq = v.print ? floorl(total_time / timestep) / 100 : ceill(total_time / timestep);
}

Euler::Euler(const variables &v) {
    size = v.size;
    x = std::valarray<double>(0., v.size);
    total_time = v.total_time;
    curr_step = 0;
    timestep = v.dt;
    print_freq = v.print ? floorl(total_time / timestep) / 100 : ceill(total_time / timestep);
}

Euler::~Euler(){

}

void Euler::integrate(Shear & n) {
    while (timestep * curr_step++ < total_time) {
        step(n);
    }
}

void Euler::step(Shear &e) {
    ++curr_step;
    if (curr_step % print_freq == 0){
        print();
    }
    x += e.increment(x, timestep);
}

double Euler::getCharVal() const {
    Stats s{};
    for (auto i=0; i<x.size(); i++){
        s.push(x[i]);
    }
    return s.getMean();
}

