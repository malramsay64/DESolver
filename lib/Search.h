//
// Created by malcolm on 6/11/15.
//

#ifndef SHEAR_SEARCH_H
#define SHEAR_SEARCH_H

#include "stability.h"
#include "input.h"

class Search {
protected:
    double tolerance{1e-5};
    int max_iters{100};
    int iteration;
    bool isdone;
public:
    int numIters() {return iteration;};
    int done(){return isdone;};
    double getVal(double, int) { return 0; };

};

class Binary_Search : public Search {
    double max;
    double min;
    double delta;
public:
    Binary_Search();
    Binary_Search(double);
    Binary_Search(const variables& v);

    double getVal(double, int);
};

class Stochastic_Search : public Search {

};

#endif //SHEAR_SEARCH_H