#include "input.h"
#include "integrator.h"
#include "stability.h"
#include "search.h"


using namespace std;

// Global variables



int main (int argc, char** argv){

    variables v;
    set_vars(argc, argv, &v);
    double *a = (double *) malloc(v.size*sizeof(double));

    int steps = 1;
    if (v.Amax > v.deltaA) {
        steps = int((v.Amax - v.A) / v.deltaA) + 1;
    }
    for (int i = 0; i < steps; i++){
        initialise(a, v.size);
        if (v.run_search) {
            v.delta = search_delta(a, &v);
        }
        else {
            integrator(a, v);
        }

        if (v.Amax > v.deltaA) {
            v.A += v.deltaA;
            if (v.A > v.Amax) {
                v.A = v.Amax;
            }
        }
        cout << v.size << " " << v.dx << " " << v.dt << " " << v.total_time << " " << v.Q << " " << v.A << " " << v.delta << " " << v.delay << " " << stability(a, v.size) << endl;
    }

    free(a);
    return 0;
}

