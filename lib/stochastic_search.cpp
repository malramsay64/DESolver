//
// Created by malcolm on 12/11/15.
//

#include "stochastic_search.h"

using namespace std;

double precision = 5e-5;

double stochastic_upper(double *x, variables v){
    // Find max and min values
    point max;
    point min;
    point *p;
    list<point>::iterator i;
    max.pos = INFINITY;
    max.weight = 0.5;
    min.pos = -INFINITY;
    min.weight = 0.5;
    double stab, prob;
    while (max.pos == INFINITY){
        initialise(x, v.size);
        integrator(x, v);
        stab = stability(x, v.size);
        if (stab == 1){
            max.pos = v.delta + v.deltaDelta;
            v.delta -= v.deltaDelta;
        }
        else {
            v.delta += v.deltaDelta;
            v.deltaDelta *= 2;
        }
    }
    while (min.pos == -INFINITY){
        initialise(x, v.size);
        integrator(x, v);
        stab = stability(x, v.size);
        if (stab == -1){
            min.pos = v.delta - v.deltaDelta;
        }
        else {
            v.delta -= v.deltaDelta;
            v.deltaDelta *= 2;
        }

    }
    list<point> W;
    W.push_back(min);
    W.push_back(max);
    p = new point;
    p->pos = max.pos+v.deltaDelta;
    p->weight = 0;
    W.push_back(*p);
    double error = max.pos - min.pos;
    while (error > precision){
        prob = 0;
        for (i=W.begin(); i!=W.end(); i++){
            prob += i->weight;
            if (prob >= 0.5){
                prob -= i->weight/2;
                break;
            }
        }
        i->weight /= 2;
        p = new point;
        p->weight = i->weight;
        p->pos = (i->pos + next(i)->pos)/2;
        error = next(i)->pos - i->pos;
        v.delta = p->pos;
        W.insert(next(i),*p);
        initialise(x, v.size);
        integrator(x,v);
        stab = stability(x, v.size);
        // Too low
        if (stab != 1){
            for (i=W.begin(); i!=W.end(); i++){
                // Lower probability below
                if (i->pos < p->pos){
                    i->weight = (2*i->weight)/(3-prob);
                }
                    // Raise probability above
                else {
                    i->weight = (3*i->weight)/(3-prob);
                }
            }
        }
            // Too high
        else {
            for (i=W.begin(); i!=W.end(); i++){
                // Lower probability above
                if (i->pos >= p->pos){
                    i->weight =(2*i->weight)/(2+prob);
                }
                    // Raise probability below
                else {
                    i->weight = (3*i->weight)/(2+prob);
                }
            }
        }
    }
    prob = 0;
    for (i=W.begin(); i!=W.end(); i++) {
        prob += i->weight;
        if (prob > 0.5) {
            break;
        }
    }
    return i->pos;
}


double stochastic_lower(double *x, variables v){
    // Find max and min values
    point max;
    point min;
    point *p;
    list<point>::iterator i;
    max.pos = INFINITY;
    max.weight = 0.5;
    min.pos = -INFINITY;
    min.weight = 0.5;
    double stab, prob;
    while (max.pos == INFINITY){
        initialise(x, v.size);
        integrator(x, v);
        stab = stability(x, v.size);
        if (stab == 1){
            max.pos = v.delta + v.deltaDelta;
            v.delta -= v.deltaDelta;
        }
        else {
            v.delta += v.deltaDelta;
            v.deltaDelta *= 2;
        }
    }
    while (min.pos == -INFINITY){
        initialise(x, v.size);
        integrator(x, v);
        stab = stability(x, v.size);
        if (stab == -1){
            min.pos = v.delta - v.deltaDelta;
        }
        else {
            v.delta -= v.deltaDelta;
            v.deltaDelta *= 2;
        }

    }
    list<point> W;
    W.push_back(min);
    W.push_back(max);
    p = new point;
    p->pos = max.pos+v.deltaDelta;
    p->weight = 0;
    W.push_back(*p);
    double error = max.pos - min.pos;
    while (error > precision){
        prob = 0;
        for (i=W.begin(); i!=W.end(); i++){
            prob += i->weight;
            if (prob >= 0.5){
                prob -= i->weight/2;
                break;
            }
        }
        i->weight /= 2;
        p = new point;
        p->weight = i->weight;
        p->pos = (i->pos + next(i)->pos)/2;
        error = next(i)->pos - i->pos;
        v.delta = p->pos;
        W.insert(next(i),*p);
        initialise(x, v.size);
        integrator(x,v);
        stab = stability(x, v.size);
        // Too low
        if (stab == -1){
            for (i=W.begin(); i!=W.end(); i++){
                // Lower probability below
                if (i->pos < p->pos){
                    i->weight = (2*i->weight)/(3-prob);
                }
                    // Raise probability above
                else {
                    i->weight = (3*i->weight)/(3-prob);
                }
            }
        }
            // Too high
        else {
            for (i=W.begin(); i!=W.end(); i++){
                // Lower probability above
                if (i->pos >= p->pos){
                    i->weight =(2*i->weight)/(2+prob);
                }
                    // Raise probability below
                else {
                    i->weight = (3*i->weight)/(2+prob);
                }
            }
        }
    }
    prob = 0;
    for (i=W.begin(); i!=W.end(); i++) {
        prob += i->weight;
        if (prob > 0.5) {
            break;
        }
    }
    return i->pos;
}