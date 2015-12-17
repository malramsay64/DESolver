#include <random>
#include <stdexcept>

#ifndef noise_h
#define noise_h

class Noise {
    std::normal_distribution<double> distribution;
    std::random_device generator;
public:
    Noise(double=1);
    double getVal();
};

#endif
