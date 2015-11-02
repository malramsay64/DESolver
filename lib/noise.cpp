#include "noise.h"

std::normal_distribution<double> distribution(0, 1);
std::default_random_engine generator;

double noise(double Q){
    return distribution(generator)*Q;
}
