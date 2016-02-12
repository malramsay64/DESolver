//
// Created by malcolm on 4/12/15.
//
/* Equation.h: Creating the Equation class
 *
 * This is envisioned to work with a number of different types of equations,
 * with the ability to solve them using a variety of techniques. The more
 * complicated equation classes are envisioned to be comprised of a many of
 * the simpler equation classes.
 *
 * It was envisioned that all Equation classes had the function solve(), however
 * with the implementation having the integrator as the handle makes this difficult
 * for the Numerical Differential Equations.
 *
 */

/* DEquation : Differential Equations
 *
 * This is a subclass for solving differential equations.
 */

/* NDEquation : Numerical Differential Equations
 *
 * This subclass is to hold a variety of numerical differential equations. Ultimately
 * I may have to also break this up into Parabolic, Elliptical and Hyperbolic but that
 * is for another time.
 *
 * All NDEs have will have the function increment, returning an array with the appropriate
 * increment. A new valarray is returned so as to allow further functions to be performed.
 *
 */

/* Finite Difference :
 *
 * This implements the finite difference approximation.
 */

/* Finite_Double_Difference :
 *
 * This implements the finite difference approximation of the second derivative.
 *
 * The simplicity of this function allows it to be used as a building block for other functions.
 */

/* Shear :
 *
 * This implements a stochastic differential equation to investigate the effect of the
 * shear stress on the crystal liquid equilibrium.
 *
 */

#include <valarray>
#include <iomanip>
#include <string>
#include <iostream>
#include "Search.h"
#include "noise.h"
#include "Integrator.h"

#ifndef SHEAR_EQUATION_H
#define SHEAR_EQUATION_H

class Equation {
public:
    virtual double solve()=0;
};

class DEquation: public Equation {
public:
    DEquation() : Equation() {};
};


class NDEquation: public DEquation {
protected:
    Euler myIntegrator;
public:

    NDEquation() : DEquation(), myIntegrator(Euler{}) {};
    NDEquation(const Euler &ni) : DEquation(), myIntegrator(ni) {};
    NDEquation(const NDEquation &n) : DEquation(), myIntegrator(n.myIntegrator) {};

    virtual double solve(){ return 0; };
    virtual double Integrate() { myIntegrator.integrate(*this); };
    virtual std::valarray<double> increment(const std::valarray<double> &, double) const;

    friend std::ostream &operator<<(std::ostream &, const NDEquation &);
};


class Finite_Difference: public NDEquation {
public:
    Finite_Difference() : NDEquation() {};

    double solve() { return 0; };

    std::valarray<double> increment(const std::valarray<double> &, double=1) const ;
};

class Finite_Double_Difference: public NDEquation {
public:
    Finite_Double_Difference() : NDEquation() {};

    double solve() { return 0; };

    std::valarray<double> increment(const std::valarray<double> &, double=1) const ;
};

class Shear : public NDEquation {
    const double A;
    const double Q;
    double D;
    const bool runSearch;
    const Finite_Double_Difference d2;

    Binary_Search search;
    Noise n{};
public:
    Shear() : NDEquation(Euler{}), A(0), D(0), Q(1), runSearch(false), d2(Finite_Double_Difference{}){};
    Shear(double A, double D=0, double Q=1, const Euler &n=Euler{}) : NDEquation(n), A(A), D(D), Q(Q), runSearch(false), d2(Finite_Double_Difference{}) {};
    Shear(const variables& v) : NDEquation(Euler{v}), A(v.A), D(v.delta), Q(v.Q), runSearch(v.run_search), d2(Finite_Double_Difference{}) {};
    Shear(const Shear &s) : NDEquation(s.myIntegrator), A(s.A), D(s.D), Q(s.Q), runSearch(s.runSearch), d2(s.d2) {};

    double getA() const { return A; };
    double getQ() const { return Q; };
    double getD() const { return D; };
    double getTotalTime() const {return myIntegrator.getTotalTime(); };
    double getTimestep() const {return myIntegrator.getTimestep(); };
    double getSize() const {return myIntegrator.getSize();};
    double getPrintFreq() const {return myIntegrator.getPrintFreq(); };
    double getCurrStep() const {return myIntegrator.getCurrStep(); };
    double getCharVal() const {return myIntegrator.getCharVal(); };
    const Euler getIntegrator() const { return myIntegrator; };

    void printX() const;
    double getRand() { return n.getVal(); };

    std::valarray<double> increment(const std::valarray<double> &, double);
    double Integrate();
    double solve();

    friend std::ostream &operator<<(std::ostream &os, const Shear &s);
};


#endif //SHEAR_EQUATION_H
