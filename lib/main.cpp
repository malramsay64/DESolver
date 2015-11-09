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

    if (v.run_search) {
        v.delta = search_delta(a, v);
    }
    for (int i=0; i<v.size; i++){
        a[i] = 0;
    }

    integrator(a, v);
    cout << v.size << " " << v.dx << " " << v.dt << " " << v.total_time << " " << v.Q << " " << v.A << " " << v.delta << " " << v.delay << " " << stability(a, v.size) << endl;
    free(a);
    return 0;
}

