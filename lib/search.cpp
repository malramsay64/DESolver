//
// Created by malcolm on 9/11/15.
//
#include "search.h"

using namespace std;

double search_delta(double * x, variables v) {
    double deltaDelta = v.deltaDelta;
    double deltaLast = 0;
    int stabLast = -10;
    int stab = -10;
    if (v.deltaA != 0){
        deltaDelta = v.deltaA;
    }
    while (stab != 0) {
        initialise(x, v.size);
        // Integration
        integrator(x, v);

        // Comparison
        stab = stability(x, v.size);
        // Determination of next step
        if (abs(stab) <= 1) {
            v.delta -= stab * deltaDelta;
            if (stabLast != -10 && stabLast != stab) {
                deltaDelta /= 2;
            }
            stabLast = stab;
            deltaLast = v.delta;

        }
            // Moves out of stability
        else if (stabLast != 2) {
            v.delta = (v.delta + deltaLast) / 2;
            deltaDelta /= 2;
            stabLast = stab;
        }
            // Instability
        else {
            return NAN;
        }
    }
    return v.delta;
}

double search_upper(double *x, variables v){
    int trials = 3;
    int stabs[trials];
    double max = INFINITY;
    double min = -INFINITY;
    double dDelta = 0.05;
    if (v.deltaDelta != 0){
        dDelta = fabs(v.deltaDelta);
    }
    int stab = -10;
    while (fabs(max - min) > 1e-4){
        for (int i=0; i<trials;i++){
            initialise(x, v.size);
            integrator(x, v);

            stabs[i] = stability(x, v.size);
        }
        stab = mode(stabs, trials);
        if (stab == 1){
            max = v.delta;
            if (min > -INFINITY){
                v.delta = (max + min) / 2;
            }
            else {
                v.delta = v.delta - dDelta;
                dDelta *= 2;
            }
        }
        else if (stab == 0 || stab == -1){
            min = v.delta;
            if (max < INFINITY){
                v.delta = (max + min)/2;
            }
            else {
                v.delta += dDelta;
                dDelta *= 2;
            }
        }
    }
    return v.delta;
}

double search_lower(double *x, variables v){
    int trials = 3;
    int stabs[trials];
    double max = INFINITY;
    double min = -INFINITY;
    double dDelta = 0.05;
    if (v.deltaDelta != 0){
        dDelta = fabs(v.deltaDelta);
    }
    int stab = -10;
    while (fabs(max - min) > 1e-4){
        for (int i=0; i<trials;i++) {
            initialise(x, v.size);
            integrator(x, v);

            stabs[i] = stability(x, v.size);
        }
        stab = mode(stabs, trials);
        if (stab == -1){
            min = v.delta;
            if (max < INFINITY){
                v.delta = (max + min) / 2;
            }
            else {
                v.delta +=dDelta;
                dDelta *= 2;
            }
        }
        else if (stab == 0 || stab == 1){
            max = v.delta;
            if (min > -INFINITY){
                v.delta = (max + min)/2;
            }
            else {
                v.delta -= dDelta;
                dDelta *= 2;
            }
        }
    }
    return v.delta;
}