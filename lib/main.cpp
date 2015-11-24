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
            int print = v.print;
            v.print = 0;
            max = stochastic_upper(a, v);
            min = stochastic_lower(a, v);
            v.delta = (max+min)/2;
            v.print = print;
            integrator(a,v);
        }
        else if (v.run_search) {
            int print = v.print;
            v.print = 0;
            v.delta = search_delta(a, v);
            v.print = print;
            integrator(a,v);
        }
        else {
            integrator(a, v);
        }
        cout << v.size << " " << v.dx << " " << v.dt << " " << v.total_time << " " << v.Q << " " << v.A << " " \
             << min << " " << v.delta << " " << max << " " << v.delay << " " << stability(a, v.size) << " " << \
             mean(a, v.size) << endl;

        if (v.Amax > v.deltaA) {
            v.A += v.deltaA;
            if (v.A > v.Amax) {
                v.A = v.Amax;
            }
        }
    }

    free(a);
    return 0;
}

