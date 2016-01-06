#include <random>
#include <stdexcept>

#ifndef noise_h
#define noise_h

class Noise {
    std::normal_distribution<double> distribution;
    std::random_device generator;
    double stdev;
public:
    Noise(double=1);
    double getVal();

    Noise(const Noise&);
    Noise operator=(const Noise& n) { return Noise{n};};
};

#endif
