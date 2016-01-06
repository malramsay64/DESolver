//
// Created by malcolm on 4/12/15.
//

#include "Equation.h"

using namespace std;

DEquation::DEquation() { }

NDEquation::NDEquation() { }

Finite_Difference::Finite_Difference() { }
Finite_Difference::~Finite_Difference() { }

double Finite_Difference::solve() {
    return 0;
}


valarray<double> Finite_Difference::increment(const std::valarray<double> &x, double dt) const {
    valarray<double> h(0., x.size());
    if (x.size() < 2) return h;
    for (size_t i = 0; i < x.size()-1; i++){
        h[i] = (x[i+1] - x[i]);
    }
    // Edge cases
    h[x.size()-1] = (x[0] - x[x.size()-1]);
    return h;
}

Finite_Double_Difference::Finite_Double_Difference()  {
    myIntegrator = Euler{};
}

Finite_Double_Difference::Finite_Double_Difference(const Finite_Double_Difference &){
    myIntegrator = Euler{};
}

Finite_Double_Difference::~Finite_Double_Difference(){
}

double Finite_Double_Difference::solve() {
   return 0;
}

valarray<double> Finite_Double_Difference::increment(const valarray<double> &x, double dt) const {
    valarray<double> h(0., x.size());
    if (x.size() < 3) return h;
    double dx2 = pow(1./x.size(),2);
    for (size_t i = 1; i < x.size()-1; i++){
        h[i] = (x[i-1]+x[i+1] - 2*x[i])/dx2;
    }
    // Edge cases
    h[0] = (x[x.size()-1]+x[1] - 2*x[0])/dx2;
    h[x.size()-1] = (x[x.size()-2]+x[0] - 2*x[x.size()-1])/dx2;
    return h;
}

Shear::Shear() {
    A = 0;
    D = 0;
    Q = 1;
    myIntegrator = Euler{};
}

Shear::Shear(double a,double d, double q){
    A = a;
    D = d;
    Q = q;
    myIntegrator = Euler{};
}

Shear::Shear(const Shear &s) {
    A = s.A;
    D = s.D;
    Q = s.Q;
    myIntegrator = Euler{};
}

Shear::Shear(const Euler & ni, double a, double d, double q) {
    A = a;
    D = d;
    Q = q;
    myIntegrator = ni;
}

Shear::Shear(const variables& v){
    A = v.A;
    D = v.delta;
    Q = v.Q;
    myIntegrator = Euler{v};
    runSearch = v.run_search;
    search = Binary_Search(v);
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

double Shear::solve() {
    if (runSearch){
        double meanVal = 0;
        while (!search.done()){
            meanVal = Integrate();
            cout << "Trying: " << D << " Value: " << scientific << meanVal << endl;
            D = search.getVal(D, (meanVal < 0 ? -1 : 1) );
            myIntegrator.reset();
        }
        return meanVal;
    }
    else {
        return Integrate();
    }
}

double Shear::Integrate() {
    myIntegrator.integrate(*this);
    return myIntegrator.getCharVal();
}

void Shear::printX() const {
    myIntegrator.print();
}

valarray<double> Shear::increment(const std::valarray<double> &x, double dt) {
    valarray<double> h = d2.increment(x, dt);
    double noise_factor = Q/sqrt(dt/(pow(1./x.size(),2)));
    for (auto i =0; i< x.size(); i++){
        if (h[i] < 0) {
            h[i] += h[i]*A;
        }
        h[i] += D;
        h[i] += n.getVal()*noise_factor;
        h[i] *= dt;
    }
    return h;
}

ostream &operator<<(ostream &os, const Shear &s) {
    return os << s.getA() << ' ' << s.getD() << ' ' << s.getQ();
}

ostream &operator<<(ostream &os, const NDEquation &s) {
    return os;
}

valarray<double> NDEquation::increment(const std::valarray<double> &x, double dt) const {
    return valarray<double>(0., x.size());
}

