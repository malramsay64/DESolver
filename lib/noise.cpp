#include "noise.h"



Noise::Noise(double a){
    /*
     * Precondition: a not negative
     */
    (a < 0) ? throw std::invalid_argument{"a"} : distribution = std::normal_distribution<double>{0, a};
}

double Noise::getVal(){
    return distribution(generator);
}
