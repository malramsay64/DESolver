//
// Created by malcolm on 9/11/15.
//
#include "search.h"

using namespace std;

double search_delta(double * x, variables v) {
    double deltaDelta = v.deltaA;
    double deltaLast = 0;
    double delta = v.delta;
    int stabLast = -10;
    int stab = -10;
    while (stab != 0) {
        // Initialize vector
        for (int i = 0; i < v.size; i++) {
            x[i] = 0;
        }
        // Integration
        integrator(x, v);

        // Comparison
        stab = stability(x, v.size);
        // Determination of next step
        if (abs(stab) <= 1) {
            delta -= stab * deltaDelta;
            if (stabLast != stab) {
                deltaDelta /= 2;
            }
            stabLast = stab;
            deltaLast = delta;

        }
            // Instability
        else {
            delta = (delta + deltaLast) / 2;
        }
    }
    return delta;
}

