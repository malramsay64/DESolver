//
// Created by malcolm on 4/12/15.
//

#include "Equation.h"

std::valarray<double> Finite_Difference::increment(const std::valarray<double> &x, double dt) const {
    std::valarray<double> h(0., x.size());
    if (x.size() < 2) return h;
    for (size_t i = 0; i < x.size()-1; i++){
        h[i] = (x[i+1] - x[i]);
    }
    // Edge cases
    h[x.size()-1] = (x[0] - x[x.size()-1]);
    return h;
}

std::valarray<double> Finite_Double_Difference::increment(const std::valarray<double> &x, double dt) const {
    std::valarray<double> h(0., x.size());
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

double Shear::solve() {
    if (runSearch){
        double meanVal = 0;
        std::cerr << std::defaultfloat;
        std::cerr << *this << std::endl;
        while (!search.done()){
            myIntegrator.reset();
            std::cerr << "  " << search.numIters() << " Trying: " << D;
            meanVal = Integrate();
            std::cerr << " Value: " << meanVal << std::endl;
            D = search.getVal(D, (meanVal < 0 ? -1 : 1) );
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

std::valarray<double> Shear::increment(const std::valarray<double> &x, double dt) {
    std::valarray<double> h = move(d2.increment(x, dt));
    double noise_factor = Q*sqrt((pow(1./x.size(),2))/dt);
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

std::ostream &operator<<(std::ostream &os, const Shear &s) {
    return os << s.getA() << ' ' << s.getD() << ' ' << s.getQ() << ' ' << s.myIntegrator;
}

std::ostream &operator<<(std::ostream &os, const NDEquation &s) {
    return os;
}

std::valarray<double> NDEquation::increment(const std::valarray<double> &x, double dt) const {
    return std::valarray<double>(0., x.size());
}

