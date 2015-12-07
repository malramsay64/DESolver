//
// Created by malcolm on 4/12/15.
//

#include <valarray>
#include <iomanip>

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
    std::valarray<double> increment(std::valarray<double> &, double);

    std::ostream &operator<<(std::ostream &);

    friend std::ostream &operator<<(std::ostream &, const NDEquation &);
};

class Finite_Difference: public NDEquation {
    std::valarray<double> increment(std::valarray<double> &, double);
};

class Finite_Double_Difference: public  NDEquation {
public:
    Finite_Double_Difference();

    std::valarray<double> increment(std::valarray<double> &, double);
};

class Shear : public NDEquation {
    double A;
    double Q;
    double D;
    Finite_Double_Difference d2{};
public:
    Shear();
    Shear(double, double, double);
    Shear(double);

    Shear(const Shear &);

    double getA() const;

    double getQ() const;

    double getD() const;

    std::valarray<double> increment(std::valarray<double> &, double);

    friend std::ostream &operator<<(std::ostream &, Shear &);
};


#endif //SHEAR_EQUATION_H
