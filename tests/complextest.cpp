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
    variables v;
    double x[v.size];
    for (int i=0;i<v.size;i++){
        x[i] = 0;
    }
    v.Q = 0; // No noise
    integrator_cblas(x, v);
    ASSERT_DOUBLE_EQ(0, sum(x,v.size));
}

TEST(IntegratorCBLAS, SteadyState){
    variables v;
    double x[v.size];
    for (int i=0;i<v.size;i++){
        x[i] = 0;
    }
    integrator_cblas(x, v);
    ASSERT_NEAR(0, mean(x,v.size),1./v.size);
    ASSERT_NEAR(0, stdev(x,v.size),2./v.size);
}

TEST(IntegratorCBLAS, Dampening){
    variables v;
    double x[v.size];
    double y[v.size];
    for (int i=0;i<v.size;i++){
        x[i] = 0;
    }
    integrator_cblas(x, v);
    integrator_cblas(y, v);
    v.Q = 0;
    integrator_cblas(x, v);
    ASSERT_TRUE(stdev(x,v.size)<stdev(y,v.size));
}
TEST(Integrator, NoNoiseSteadyState){
    variables v;
    double x[v.size];
    for (int i=0;i<v.size;i++){
        x[i] = 0;
    }
    v.Q = 0; // No noise
    integrator(x, v);
    ASSERT_DOUBLE_EQ(0, sum(x,v.size));
}

TEST(Integrator, SteadyState){
    variables v;
    double x[v.size];
    for (int i=0;i<v.size;i++){
        x[i] = 0;
    }
    integrator(x, v);
    ASSERT_NEAR(0, mean(x,v.size),1./v.size);
    ASSERT_NEAR(0, stdev(x,v.size),2./v.size);
}

TEST(Integrator, Dampening){
    variables v;
    double x[v.size];
    double y[v.size];
    for (int i=0;i<v.size;i++){
        x[i] = 0;
    }
    integrator(x, v);
    integrator(y, v);
    v.Q = 0;
    integrator(x, v);
    ASSERT_TRUE(stdev(x,v.size)<stdev(y,v.size));
}

TEST(Integrator, Congruency){
    variables v;
    double x[v.size];
    double y[v.size];
    for (int i=0;i<v.size;i++){
        x[i] = 0;
        y[i] = 0;
    }
    integrator(x, v);
    integrator_cblas(y, v);
    cblas_daxpy(v.size, -1, x, 1, y, 1);
    ASSERT_NEAR(0, sum(y, v.size), 1e-5);
}
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}