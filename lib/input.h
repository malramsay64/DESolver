//
// Created by malcolm on 9/11/15.
//

#ifndef SHEAR_INPUT_H
#define SHEAR_INPUT_H

#include <string>
#include <iostream>
#include <getopt.h>


struct variables{
    int size = 100;
    double Q = 1;
    double total_time = 0.01;
    double dt = 1e-6;
    double A = 0;
    double dx = 0.01;
    double delta = 0;
    int delay = 1;
    int run_search = 0;
    double Amax = 0;
    double deltaA = 0;
};

void useage();
int set_vars(int argc, char** argv, variables *v);

#endif //SHEAR_INPUT_H
