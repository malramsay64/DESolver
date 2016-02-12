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
#include <Stats.h>
#include "input.h"

class NDEquation;
class Shear;

class Integrator {

};

class Numerical_Integrator: public virtual Integrator {
protected:
    const size_t size;
    const double total_time;
    const double timestep;
    const long print_freq;
    const std::string fname;

    std::valarray<double> x;
    int curr_step;

public:
    Numerical_Integrator(): size(0), total_time(0), timestep(0), print_freq(1), fname("outfile.dat") {};

    Numerical_Integrator(size_t s, double time, double dt, int num_print=1, std::string in_fname="outfile.dat"): \
    size(s), total_time(time), timestep(dt), print_freq(floorl(total_time/timestep)/num_print), fname(in_fname) {
        curr_step = 0;
        x = std::valarray<double>(0.,size);
    };

    Numerical_Integrator(const variables& v): \
    size(v.size), total_time(v.total_time), timestep(v.dt), print_freq(v.print ? floorl(total_time / timestep) / 100 : ceill(total_time / timestep)), fname(make_fname(v)) {
        curr_step = 0;
        x = std::valarray<double>(0., size);
    }

    Numerical_Integrator(const Numerical_Integrator &ni): \
            size(ni.size), total_time(ni.total_time), timestep(ni.timestep), print_freq(ni.print_freq), fname(ni.fname) {
        curr_step = ni.curr_step;
        x = std::valarray<double>(ni.x);
    };

    size_t getSize() const {return size;};
    double getTotalTime() const {return total_time;};
    int getCurrStep() const {return curr_step;};
    long getPrintFreq() const { return print_freq;};
    double getTimestep() const { return timestep;};
    std::string getFname() const {return fname;};

    std::valarray<double> &getX() { return x;};
    std::valarray<double> const &getX() const {return x;};

    virtual void print() const;
    void reset();

    virtual void integrate(Shear &);
    virtual void step(Shear &) {};
    virtual double getCharVal() const { return 0; };

    friend std::ostream &operator<<(std::ostream &os, const Numerical_Integrator &n);
};


class Euler : public Numerical_Integrator {
public:
    void integrate(Shear &n) ;
    void integrate(NDEquation &n);
    void step(Shear &e);
    void step(NDEquation &n);
    double getCharVal() const;

    Euler() : Numerical_Integrator(variables{}) {};
    Euler(const variables &v) : Numerical_Integrator(v) {};


    friend std::ostream &operator<<(std::ostream &os, const Euler &n);
};


#endif //SHEAR_INTEGRATOR_H
