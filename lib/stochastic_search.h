//
// Created by malcolm on 12/11/15.
//

#ifndef SHEAR_STOCHASTIC_SEARCH_H
#define SHEAR_STOCHASTIC_SEARCH_H

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include "integrator.h"
#include "stability.h"
#include "input.h"

double stochastic_lower(double *x, variables v);
double stochastic_upper(double *x, variables v);

struct point{
    double pos;
    double weight;
    friend bool operator<(const point& lhs, const point& rhs) {
        return lhs.pos < rhs.pos;
    }
    friend bool operator==(const point& lhs, const point& rhs) {
        return lhs.pos == rhs.pos;
    }
    friend bool operator>(const point& lhs, const point& rhs) {
        return lhs.pos > rhs.pos;
    }
};


#endif //SHEAR_STOCHASTIC_SEARCH_H
