//
// Created by malcolm on 4/12/15.
//

#include "Equation.h"

using namespace std;
Finite_Double_Difference::Finite_Double_Difference() {
}

valarray<double> Finite_Double_Difference::increment(valarray<double> &x, double dt) {
    double dx2 = pow(1./x.size(),2);
    valarray<double> h(0., x.size());
    for (size_t i = 1; i < x.size()-1; i++){
        h[i] = (x[i-1]+x[i+1] - 2*x[i])/dx2;
    }
    // Edge cases
    h[0] = (x[x.size()-1]+x[1] - 2*x[0])/dx2;
    h[x.size()-1] = (x[x.size()-2]+x[0] - 2*x[x.size()-1])/dx2;
    return h;
}

Shear::Shear(){
    A = 0;
    D = 0;
    Q = 1;
}

Shear::Shear(double a){
    A = a;
    D = 0;
    Q = 1;
}

Shear::Shear(double a,double d, double q){
    A = a;
    D = d;
    Q = q;
}

Shear::Shear(const Shear &s) {
    A = s.A;
    D = s.D;
    Q = s.Q;
}

double Shear::getA() const {
    return A;
}

double Shear::getQ() const {
    return Q;
}

double Shear::getD() const {
    return D;
}

ostream &operator<<(ostream &os, const Shear &s) {
    return os << s.getA() << ' ' << s.getD() << ' ' << s.getQ();
}

ostream &operator<<(ostream &os, const NDEquation &s) {
    return os;
}

valarray<double> NDEquation::increment(std::valarray<double> &x, double dt) {
    return valarray<double>(0., x.size());
}

valarray<double> Shear::increment(std::valarray<double> &x, double dt) {
    valarray<double> h = move(d2.increment(x, dt));
    for (auto i =0; i< x.size(); i++){
        if (h[i] < 0) {
            h[i] += h[i]*A;
        }
        h[i] += D;
        h[i] *= dt;
    }
    return h;
}