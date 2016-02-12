#include "noise.h"



Noise::Noise(double a){
    /*
     * Precondition: a non-negative
     */
    (a < 0) ? throw std::invalid_argument{"a"} : distribution = std::normal_distribution<double>{0, a};
    stdev = a;
}

Noise::Noise(const Noise &n) {
    distribution = std::normal_distribution<double>{0, n.stdev};
}

double Noise::getVal(){
    return distribution(generator);
}
