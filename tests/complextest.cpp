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

TEST(Integrator, NoNoiseSteadyState){
    int size = 100;
    double x[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
    }
    double Q = 0; // No noise
    integrator(x, size, 1./size, Q);
    ASSERT_DOUBLE_EQ(0, sum(x,size));
}

TEST(Integrator, SteadyState){
    int size = 100;
    double x[size];
    for (int i=0;i<size;i++){
        x[i] = 0;
    }
    double Q = 1;
    integrator(x, size, 1./size, Q);
    ASSERT_NEAR(0, mean(x,size),1./size);
    ASSERT_NEAR(0, stdev(x,size),2./size);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}