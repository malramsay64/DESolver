//
// Created by malcolm on 3/11/15.
//
#include <gtest/gtest.h>
#include "../lib/integrator.h"
#include "../lib/functions.h"
#include "../lib/search.h"
#include "../lib/stochastic_search.h"

TEST(Integrator, Timestep){
    ASSERT_DOUBLE_EQ(1e-3,timestep(1./100,0));
    ASSERT_DOUBLE_EQ(2.5e-7, timestep(1./100,1));
    ASSERT_DOUBLE_EQ(2.5e-7, timestep(1./100,-1));
}

TEST(Integrator, NoNoiseSteadyState){
    variables v;
    double x[v.size];
    initialise(x, v.size);
    v.Q = 0; // No noise
    integrator(x, v);
    ASSERT_DOUBLE_EQ(0, sum(x,v.size));
}

TEST(Integrator, SteadyState){
    variables v;
    double x[v.size];
    initialise(x, v.size);
    integrator(x, v);
    ASSERT_NEAR(0, mean(x,v.size),1./v.size);
    ASSERT_NEAR(0, stdev(x,v.size),2./v.size);
}

TEST(Integrator, Dampening){
    variables v;
    double x[v.size];
    double y[v.size];
    initialise(x, v.size);
    integrator(x, v);
    integrator(y, v);
    v.Q = 0;
    integrator(x, v);
    ASSERT_TRUE(stdev(x,v.size) < stdev(y,v.size));
}


TEST(Search, Known){
    variables v;
    v.dt = 1e-6;
    v.total_time = 0.1;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    ASSERT_DOUBLE_EQ(0, search_delta(x, v));
}

TEST(Search, CloseSinglePos){
    variables v;
    v.delta = 0.1;
    v.size = 100;
    v.dt = 1e-7;
    v.total_time = 0.1;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    ASSERT_NEAR(0, search_delta(x,  v), 1e-3);
}

TEST(Search, Upper){
    variables v;
    v.delta = 0.1;
    v.size = 100;
    v.dt = 1e-6;
    v.total_time = 0.01;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    ASSERT_NEAR(0.003, search_upper(x,  v), 1e-3);
}

TEST(Search, Lower){
    variables v;
    v.delta = 0.1;
    v.size = 100;
    v.dt = 1e-6;
    v.total_time = 0.01;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    ASSERT_NEAR(-0.003, search_lower(x,  v), 1e-3);
}

TEST(Search, Range){
    variables v;
    v.delta = 0.1;
    v.size = 100;
    v.dt = 1e-6;
    v.total_time = 0.01;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    double min = search_lower(x,v);
    double max = search_upper(x,v);
    ASSERT_NEAR(0.006,max-min, 4e-3);
}

TEST(Search, CloseSingleNeg){
    variables v;
    v.delta = -0.1;
    v.size = 100;
    v.dt = 1e-7;
    v.total_time = 0.1;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    ASSERT_NEAR(0, search_delta(x,  v), 1e-3);
}

TEST(Search, ClosePos){
    variables v;
    v.delta = 0.175;
    v.size = 100;
    v.dt = 1e-7;
    v.total_time = 0.1;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    ASSERT_NEAR(0, search_delta(x,  v), 1e-3);
}

TEST(Search, CloseNeg){
    variables v;
    v.delta = -0.175;
    v.size = 100;
    v.dt = 1e-7;
    v.total_time = 0.1;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    ASSERT_NEAR(0, search_delta(x,  v), 1e-3);
}

TEST(Search, Unstable){
    variables v;
    v.total_time = 0.001;
    v.dt = 1e-4;
    v.size = 1000;
    v.A = 0.5;
    v.delta = 0.132;
    v.delay = 5;
    double x[v.size];
    initialise(x, v.size);
    ASSERT_TRUE(isnan(search_delta(x,  v)));
}

TEST(Stochastic, Comparison){
    variables v;
    v.total_time = 0.001;
    v.dt = 1e-6;
    v.size = 100;
    v.A = 0;
    v.Q = 0;
    v.delta = 0.1;
    double x[v.size];
    initialise(x, v.size);
    double standard = search_lower(x, v);
    double stochastic = stochastic_lower(x, v);
    ASSERT_NEAR(standard, stochastic, 1e-3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
