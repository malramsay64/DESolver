//
// Created by malcolm on 4/12/15.
//

#ifndef SHEAR_INTEGRATOR_H
#define SHEAR_INTEGRATOR_H


#include <glob.h>
#include <string>
#include <cmath>
#include <valarray>
#include <iostream>
#include <fstream>
#include "Equation.h"

class Integrator {
public:

};

class Numerical_Integrator: public Integrator {
protected:
    NDEquation eq;
    size_t size;
    std::valarray<double> x;
    double total_time;
    int curr_step;
    double timestep;
    long print_freq;
    std::ofstream outfile;
    virtual void step() = 0;
public:
    Numerical_Integrator();
    Numerical_Integrator(NDEquation,size_t, double, double);
    Numerical_Integrator(NDEquation,size_t, double, double, int);
    Numerical_Integrator(NDEquation,size_t, double, double, int, std::string);
    void print();
};

class Euler : public Numerical_Integrator {
public:
    void step();
};

#endif //SHEAR_INTEGRATOR_H
