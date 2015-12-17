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

#ifndef SHEAR_EQUATION_H
#define SHEAR_EQUATION_H


class Equation {
public:
    //virtual void solve()=0;
};

class DEquation: public Equation {
public:

};


class NDEquation: public  DEquation{
public:
    std::valarray<double> increment(const std::valarray<double> &, double);

    friend std::ostream &operator<<(std::ostream &, const NDEquation &);
};

class Finite_Difference: public NDEquation {
public:
    Finite_Difference();

    std::valarray<double> increment(const std::valarray<double> &, double=1);
};

class Finite_Double_Difference: public  NDEquation {
public:
    Finite_Double_Difference();

    std::valarray<double> increment(const std::valarray<double> &, double=1);
};

class Shear : public NDEquation {
    double A;
    double Q;
    double D;
    Finite_Double_Difference d2{};
public:
    Shear();
    Shear(double A, double D=0, double Q=1);

    Shear(const Shear &);

    double getA() const;

    double getQ() const;

    double getD() const;

    std::valarray<double> increment(const std::valarray<double> &, double);

    friend std::ostream &operator<<(std::ostream &os, const Shear &s);
};


#endif //SHEAR_EQUATION_H
