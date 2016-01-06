#include "input.h"
#include "Integrator.h"
#include "Equation.h"

using namespace std;

// Global variables



int main (int argc, char** argv){
    Shear i{get_vars(argc, argv)};
    i.solve();
    cout << i << endl;
    return 0;
}

