//
// Created by malcolm on 9/11/15.
//
#include "integrator.h"
#include "stability.h"

using namespace std;

int main(int argc, char * argv[]){
    // Variables
    int size = 1000;
    int delay = 5;
    double Q = 1;
    double total_time = 0.1;
    double dx = 1./size;
    double dt = 1e-7; //timestep(dx, size);
    double delta = 0;
    double *a = (double *) malloc(size*sizeof(double));

    double A = 0;
    double Amax = 1;
    double deltaA = 0.05;
    double deltaDelta = 0.1;
    double deltaLast = 0;
    int stabLast = -10;
    int steps = int((Amax-A)/deltaA) + 1;
    int stab;
    //cout << steps <<endl;
    for (int i=0; i<steps; i++){
        stab = -10;

        while (stab != 0) {
            // Initialize vector
            for (int i = 0; i < size; i++) {
                a[i] = 0;
            }
            // Integration
            //cout << "Integration " << "size " << size << " dx " << dx << " dt " << dt << " total_time " << total_time << " Q " << Q << " A " << A << " delta " << delta << " delay " << delay << endl;
            integrator(a, size, dx, dt, total_time, Q, A, delta, delay);

            // Comparison
            stab = stability(a, size);
            //cout << "A " << A << " Delta " << delta << " Stab " << stab << endl;
            // Determination of next step
            if (abs(stab) <= 1){
                delta -= stab*deltaDelta;
                if (stabLast != stab){
                    deltaDelta /= 2;
                }
                stabLast = stab;
                deltaLast = delta;

            }
                // Instability
            else {
                delta = (delta + deltaLast)/2;
            }
        }
        //cout << "Final:" << endl;
        //cout << "A " << A << " Delta " << delta << endl;
        cout << A << " " << delta << endl;
        //cout << endl;
        A += deltaA;
        deltaDelta = 0.1;
        delta = round(10*delta)/10.;
    }
}
