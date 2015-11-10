//
// Created by malcolm on 9/11/15.
//

#include "input.h"
#include "integrator.h"

using namespace std;

void useage(){
    cout << \
           "Input variables\n"
            "    -s  --size\n"
            "        The number of x values\n\n"
            "    -q  \n"
            "        The stdev of the random number generator\n\n"
            "    -t  --total_time\n"
            "        The total runtime of the simulation\n\n"
            "    -a  A\n"
            "        The magnitude of the shear force\n\n"
            "    -x  --dx\n"
            "        The size of the steps in x\n\n"
            "    -d  --delta\n"
            "        The temperature of the system\n\n"
            "    -f  --dt\n"
            "        The size of each timestep\n\n"
            "    -m  --delay\n"
            "        Noise is added every m timesteps\n\n"
            "    -A  --Amax\n"
            "        Maximum A value"
    << endl;
}

int set_vars(int argc, char** argv, variables *v){
    int opt;
    int option_index;
    (*v).dt = 0;
    (*v).dx = 0;
    static struct option long_options[] = {
            {"search", no_argument, &(*v).run_search, 1},
            {"size", required_argument, 0, 's'},
            {"total_time", required_argument, 0, 't'},
            {"dx"  , required_argument, 0, 'x'},
            {"dt"  , required_argument, 0, 'f'},
            {"delta", required_argument, 0, 'd'},
            {"delay", required_argument, 0, 'm'},
            {"help", no_argument,      0, 'h'},
            {"deltaA", required_argument, 0, 'D'},
            {"Amax", required_argument, 0, 'A'}
    };
    while ((opt = getopt_long(argc, argv, "s:q:t:a:x:d:f:hm:",long_options, &option_index)) != -1){
        switch (opt) {
            case 0:
                break;
            case 's':
                (*v).size = atoi(optarg);
                break;
            case 'q':
                (*v).Q = atof(optarg);
                break;
            case 't':
                (*v).total_time = atof(optarg);
                break;
            case 'a':
                (*v).A = atof(optarg);
                break;
            case 'A':
                (*v).Amax = atof(optarg);
                break;
            case 'D':
                (*v).deltaA = atof(optarg);
                break;
            case 'x':
                (*v).dx = atof(optarg);
                break;
            case 'd':
                (*v).delta = atof(optarg);
                break;
            case 'f':
                (*v).dt = atof(optarg);
                break;
            case 'm':
                (*v).delay = atoi(optarg);
                break;
            case 'h':
                useage();
                return 0;
            case '?':
                if (optopt == 's' || optopt == 'Q') {
                    cerr << "Option -" << toascii(optopt) << " requires an argument." << endl;
                }
                else { cerr << "Unknown option -" << toascii(optopt) << endl;
                }
                return 1;
            default:
                abort();
        }
    }
    if ((*v).dx == 0){
        (*v).dx = 1./((*v).size);
    }
    if ((*v).dt == 0){
        (*v).dt = timestep((*v).dx, (*v).size);
    }
    return 0;
}