#include <gtest/gtest.h>
#include "../lib/noise.h"
#include "../lib/functions.h"
#include "../lib/differentiate.h"


TEST(Stats, Mean){
    double x[] {-1.0, 1.0, -1.0, 1.0};
    ASSERT_DOUBLE_EQ(0.0, mean(x,4));
    double y[] {-1.0, 1.0, 2.0, 3.0};
    ASSERT_DOUBLE_EQ(1.25, mean(y,4));
}

TEST(Stats, Variance){
    double x[] {1.0};
    ASSERT_EQ(1, isnan(variance(x,1)));
    double y[] {1.0, 1.0, 1.0, 1.0};
    ASSERT_DOUBLE_EQ(0.0, variance(y,4));
    double z[] {-1, -1, 0, 1, 1};
    ASSERT_DOUBLE_EQ(1, variance(z,5));
}

TEST(Stats, Stdev){
    double x[] {1.0};
    ASSERT_EQ(1, isnan(stdev(x,1)));
    double y[] {1.0, 1.0, 1.0, 1.0};
    ASSERT_DOUBLE_EQ(0.0, stdev(y,4));
    double z[] {-1, -1, 0, 1, 1};
    ASSERT_DOUBLE_EQ(1, stdev(z,5));
}

TEST(Stats, Sum){
    double x[] {1,2,3,4};
    ASSERT_DOUBLE_EQ(10, sum(x,4));
    double y[] {-1,-2,1,2};
    ASSERT_DOUBLE_EQ(0, sum(y,4));
    double z[] {-1,-2,-3,-4};
    ASSERT_DOUBLE_EQ(-10, sum(z,4));
}

TEST(Noise, Mean){
    int size = 100;
    double Q = 1.0;
    double n[size];
    noise(n, size, Q);
    ASSERT_NEAR(0, mean(n,size), 2./size);
}

TEST(Noise, Stdev){
    int size = 100;
    double Q = 1.0;
    double n[size];
    noise(n, size, Q);
    ASSERT_NEAR(Q, stdev(n,size), 5./size);
}

TEST(Differentiate, FiniteDifferenceDouble){
    double per[] {-2,1,0,0,0,1,\
                  1,-2,1,0,0,0,\
                  0,1,-2,1,0,0,\
                  0,0,1,-2,1,0,\
                  0,0,0,1,-2,1,\
                  1,0,0,0,1,-2 };
    int size = 6;
    double H[size*size];
    finite_difference_double(H, size);
    cblas_daxpy(size*size,-1,per,1,H,1);
    ASSERT_DOUBLE_EQ(0,sum(H,size*size));
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}