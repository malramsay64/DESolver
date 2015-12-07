//
// Created by malcolm on 9/11/15.
//

#ifndef SHEAR_INPUT_H
#define SHEAR_INPUT_H

#include <string>
#include <iostream>
#include <getopt.h>
#include <sstream>


struct variables {
    int size = 100;
    double Q = 1;
    double total_time = 0.01;
    double dt = 1e-6;
    double A = 0;
    double dx = 0.01;
    double delta = 0;
    int delay = 1;
    int run_search = 0;
    int search_range = 0;
    double deltaDelta = 0.05;
    double Amax = 0;
    double deltaA = 0;
    int print = 0;
};

void useage();

variables &get_vars(int argc, char **argv);

std::string &&make_fname(const variables &);

#endif //SHEAR_INPUT_H
