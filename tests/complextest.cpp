//
// Created by malcolm on 3/11/15.
//
#include <gtest/gtest.h>
#include "../lib/integrator.h"
#include "../lib/functions.h"

TEST(Integrator, Timestep){
    ASSERT_DOUBLE_EQ(1e-3,timestep(1./100,0));
    ASSERT_DOUBLE_EQ(2.5e-7, timestep(1./100,1));
    ASSERT_DOUBLE_EQ(2.5e-7, timestep(1./100,-1));
}

TEST(IntegratorCBLAS, NoNoiseSteadyState){
    int size = 100;
    double total_time = 0.001;
    double x[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
    }
    double Q = 0; // No noise
    integrator_cblas(x, size, 1. / size, timestep(1. / size, 1), total_time, Q);
    ASSERT_DOUBLE_EQ(0, sum(x,size));
}

TEST(IntegratorCBLAS, SteadyState){
    int size = 100;
    double total_time = 0.001;
    double x[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
    }
    double Q = 1;
    integrator_cblas(x, size, 1. / size, timestep(1. / size, Q), total_time, Q);
    ASSERT_NEAR(0, mean(x,size),1./size);
    ASSERT_NEAR(0, stdev(x,size),2./size);
}

TEST(IntegratorCBLAS, Dampening){
    int size = 100;
    double total_time = 0.01;
    double x[size];
    double y[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
    }
    double Q = 1;
    integrator_cblas(x, size, 1. / size, timestep(1. / size, Q), timestep(1. / size, Q), Q);
    integrator_cblas(y, size, 1. / size, timestep(1. / size, Q), timestep(1. / size, Q), Q);
    Q = 0;
    integrator_cblas(x, size, 1. / size, timestep(1. / size, 1), total_time, Q);
    ASSERT_TRUE(stdev(x,size)<stdev(y,size));
}
TEST(Integrator, NoNoiseSteadyState){
    int size = 100;
    double total_time = 0.001;
    double x[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
    }
    double Q = 0; // No noise
    integrator(x, size, 1. / size, timestep(1. / size, 1), total_time, Q);
    ASSERT_DOUBLE_EQ(0, sum(x,size));
}

TEST(Integrator, SteadyState){
    int size = 100;
    double total_time = 0.001;
    double x[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
    }
    double Q = 1;
    integrator(x, size, 1. / size, timestep(1. / size, Q), total_time, Q);
    ASSERT_NEAR(0, mean(x,size),1./size);
    ASSERT_NEAR(0, stdev(x,size),2./size);
}

TEST(Integrator, Dampening){
    int size = 100;
    double total_time = 0.01;
    double x[size];
    double y[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
    }
    double Q = 1;
    integrator(x, size, 1. / size, timestep(1. / size, Q), timestep(1. / size, Q), Q);
    integrator(y, size, 1. / size, timestep(1. / size, Q), timestep(1. / size, Q), Q);
    Q = 0;
    integrator(x, size, 1. / size, timestep(1. / size, 1), total_time, Q);
    ASSERT_TRUE(stdev(x,size)<stdev(y,size));
}

TEST(Integrator, Congruency){
    int size = 100;
    double total_time = 0.01;
    double x[size];
    double y[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
        y[i] = 0;
    }
    double Q = 1;
    integrator(x, size, 1. / size, timestep(1. / size, Q), total_time, Q);
    integrator_cblas(y, size, 1. / size, timestep(1. / size, Q), total_time, Q);
    cblas_daxpy(size, -1, x, 1, y, 1);
    ASSERT_NEAR(0, sum(y, size), 1e-5);
}
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}