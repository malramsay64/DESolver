//
// Created by malcolm on 6/11/15.
//

#include "stability.h"

int stability(double *x, int size, double precision){
    double m = mean(x, size);
    double s = stdev(x, size);
    if (s < 1){
        if (fabs(m) < precision){
            return 0;
        }
        else if ( m < 0) {
            return -1;
        }
        return 1;
    }
    return 2;
}
