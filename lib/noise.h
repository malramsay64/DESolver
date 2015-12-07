#include <random>

#ifndef noise_h
#define noise_h

class Noise {
    std::normal_distribution<double> distribution;
    std::random_device generator;
public:
    Noise();
    Noise(double);
    void setAmplitude(double);
    double getVal();
};

#endif
