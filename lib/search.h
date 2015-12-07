//
// Created by malcolm on 6/11/15.
//

#ifndef SHEAR_SEARCH_H
#define SHEAR_SEARCH_H

#include "stability.h"
#include "input.h"


double search_delta(double * x, variables v);
double search_upper(double * x, variables v);
double search_lower(double * x, variables v);


#endif //SHEAR_SEARCH_H