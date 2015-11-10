//
// Created by malcolm on 9/11/15.
//
#include "search.h"

using namespace std;

double search_delta(double * x, variables *v) {
    double deltaDelta = 0.1;
    double deltaLast = 0;
    int stabLast = -10;
    int stab = -10;
    if ((*v).deltaA != 0){
        deltaDelta = (*v).deltaA;
    }
    while (stab != 0) {
        initialise(x, (*v).size);
        // Integration
        integrator(x, *v);

        // Comparison
        stab = stability(x, (*v).size);
        // Determination of next step
        if (abs(stab) <= 1) {
            (*v).delta -= stab * deltaDelta;
            if (stabLast != -10 && stabLast != stab) {
                deltaDelta /= 2;
            }
            stabLast = stab;
            deltaLast = (*v).delta;

        }
            // Moves out of stability
        else if (stabLast != 2) {
            (*v).delta = ((*v).delta + deltaLast) / 2;
        }
            // Instability
        else {
            return NAN;
        }
    }
    return (*v).delta;
}

