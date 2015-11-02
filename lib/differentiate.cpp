#include "differentiate.h"

/* 
 * Finds the second derivative using the finite difference method
 * Uses periodic boundary conditions
 */
int double_differential(double *x, double *diffx, double dx, int size, bool periodic){
    for (int i=0; i<size; i++){
        diffx[i] = (x[i-1%size]+x[i+1%size]-2*x[i])/(dx*dx);
    }
    return 0;
}
