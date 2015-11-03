#include "differentiate.h"

/*
 * Generates the matrices needed for differentiation
 */

void finite_difference_double(double *H, int size){
    // Ensure matrix initialised to 0
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            H[i*size+j] = 0;
        }
    }
    // Change necessary values
    for (int i = 1;  i<size-1; i++){
        H[i*size+i] = -2;
        H[i*size+(i-1)%size] = 1;
        H[i*size+(i+1)%size] = 1;
    }
    // Edge Cases
    H[0] = -2;
    H[size-1] = 1;
    H[1] = 1;

    H[size*size-1] = -2;
    H[size*size-2] = 1;
    H[(size-1)*size] = 1;
}

/* 
 * Finds the second derivative using the finite difference method
 * Uses periodic boundary conditions
 */
int double_differential(double *x, double *diffx, double dx, int size, bool periodic){

    for (int i=0; i<size; i++){
        diffx[i] = (x[i+1]+x[i-1]-2*x[i])/(dx*dx);
    }
    return 0;
}
