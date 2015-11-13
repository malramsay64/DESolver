#include "input.h"
#include "integrator.h"
#include "stability.h"
#include "search.h"
#include "stochastic_search.h"

using namespace std;

// Global variables



int main (int argc, char** argv){

    double max = 0;
    double min = 0;
    variables v;
    set_vars(argc, argv, &v);
    double *a = (double *) malloc(v.size*sizeof(double));

    int steps = 1;
    if (v.Amax > v.deltaA) {
        steps = int((v.Amax - v.A) / v.deltaA) + 1;
    }
    for (int i = 0; i < steps; i++){
        initialise(a, v.size);
        if (v.search_range){
            max = stochastic_upper(a, v);
            min = stochastic_lower(a, v);
            v.delta = (max+min)/2;
        }
        else if (v.run_search) {
            v.delta = search_delta(a, v);
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
        cout << v.size << " " << v.dx << " " << v.dt << " " << v.total_time << " " << v.Q << " " << v.A << " " \
             << min << " " << v.delta << " " << max << " " << v.delay << " " << stability(a, v.size) << " " << \
             mean(a, v.size) << endl;
    }

    free(a);
    return 0;
}

