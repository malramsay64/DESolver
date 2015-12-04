#include "noise.h"

Noise::Noise() {
    distribution = std::normal_distribution<double>{0,1};
}

Noise::Noise(double a){
    distribution = std::normal_distribution<double>{0,a};
}

void Noise::setAmplitude(double a) {
    distribution = std::normal_distribution<double>{0,a};
}

double Noise::getVal(){
    return distribution(generator);
}
