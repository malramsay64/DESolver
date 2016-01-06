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
#include <iomanip>
#include "input.h"

class NDEquation;
class Shear;

class Integrator {
public:

};

class Numerical_Integrator: public Integrator {
protected:
    size_t size;
    std::valarray<double> x;
    double total_time;
    int curr_step;
    double timestep;
    long print_freq;
    std::string fname;

public:
    Numerical_Integrator();

    ~Numerical_Integrator();
    Numerical_Integrator(size_t, double, double);
    Numerical_Integrator(size_t, double, double, int);
    Numerical_Integrator(size_t, double, double, int, std::string);

    Numerical_Integrator(const Numerical_Integrator &);
    Numerical_Integrator (Numerical_Integrator && );
    Numerical_Integrator& operator=(const Numerical_Integrator &) = default;

    void print() const;

    void reset();

    void integrate(Shear &);

    size_t getSize() const;

    std::valarray<double> &getX();

    double getTotalTime() const;

    int getCurrStep() const;

    long getPrintFreq() const;

    double getTimestep() const;

    virtual void step(Shear &) = 0;

    double getCharVal() const;

    friend std::ostream &operator<<(std::ostream &os, const Numerical_Integrator &n);
};

class Euler : public Numerical_Integrator {
public:
    void integrate(Shear & n) ;
    void step(Shear& e);

    Euler();
    Euler(const variables &);
    ~Euler();

    double getCharVal() const;
};


#endif //SHEAR_INTEGRATOR_H
