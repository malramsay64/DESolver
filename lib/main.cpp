#include "input.h"
#include "Integrator.h"

using namespace std;

// Global variables



int main (int argc, char** argv){
    Euler i{get_vars(argc, argv)};

    i.integrate();

    cout << i << endl;
    return 0;
}

