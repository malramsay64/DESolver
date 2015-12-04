//
// Created by malcolm on 4/12/15.
//

#include <valarray>

#ifndef SHEAR_EQUATION_H
#define SHEAR_EQUATION_H


class Equation {
public:
    virtual void solve()=0;
};

class DEquation: public Equation {
public:

};


class NDEquation: public  DEquation{
public:
    virtual std::valarray& increment(std::valarray&, double) = 0;
};

class Finite_Difference: public NDEquation {
    std::valarray& increment(std::valarray&, double);
};

class Finite_Double_Difference: public  NDEquation {
public:
    Finite_Double_Difference();
    std::valarray& increment(std::valarray&, double);
};

class Shear : public NDEquation {
    double A;
    double Q;
    double D;
    Finite_Double_Difference d2;
public:
    Shear();
    Shear(double, double, double);
    Shear(double);
    std::valarray& increment(std::valarray&, double);
};
#endif //SHEAR_EQUATION_H
