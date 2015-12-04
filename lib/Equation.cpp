//
// Created by malcolm on 4/12/15.
//

#include "Equation.h"

using namespace std;
Finite_Double_Difference::Finite_Double_Difference() {
}

valarray& Finite_Double_Difference::increment(valarray &x, double dt) {
    double dx2 = pow(1./x.size(),2);
    valarray<double> h{x.size(),0};
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

valarray& Shear::increment(std::valarray & x, double dt) {
    valarray<double> h = d2.increment(x,dt);
    for (auto i =0; i< x.size(); i++){
        if (h[i] < 0) {
            h[i] += h[i]*A;
        }
        h[i] += D;
        h[i] *= dt;
    }
    return h;
}