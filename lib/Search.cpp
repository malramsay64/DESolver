//
// Created by malcolm on 9/11/15.
//

#include "Search.h"

using namespace std;


Binary_Search::Binary_Search() {
    max = std::numeric_limits<double>::infinity();
    min = -std::numeric_limits<double>::infinity();
    delta = 0.1;
    isdone = false;
    iteration = 0;
}

Binary_Search::Binary_Search(double d) : Binary_Search() {
    delta  = d;
}
Binary_Search::Binary_Search(const variables &v): Binary_Search(){
    delta = v.deltaDelta;
}

double Binary_Search::getVal(double val, int res) {
    if (res == 0 || max - min < tolerance || iteration > max_iters){
        isdone = true;
        return val;
    }
    // First value input
    if (iteration++ == 0) {
        if (res < 0) {
            min = val;
            return val + delta;
        }
        else {
            max = val;
            return val - delta;
        }
    }
        // Getting range of values
    else if (max == std::numeric_limits<double>::infinity()){
        if (res > 0){
            max = val;
            delta = (max - min)/2;
            return (max + min)/2;
        }
        else {
            min = val;
            delta *= 2;
            return val + delta;
        }
    }
    else if (min == -std::numeric_limits<double>::infinity()) {
        if (res < 0) {
            min = val;
            delta = (max-min)/2;
            return (max + min)/2;
        }
        else {
            max = val;
            delta *= 2;
            return val - delta;
        }
    }
        // Narrowing range using binary search
    else {
        if (res < 0){
            min = val;
            delta /= 2;
            return min + delta;
        }
        else {
            max = val;
            delta /= 2;
            return max - delta;
        }
    }
}


