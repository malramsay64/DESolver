#include <gtest/gtest.h>
#include <sstream>
#include "../lib/noise.h"
#include "../lib/functions.h"
#include "../lib/differentiate.h"
#include "../lib/noise.h"
#include "../lib/Equation.h"
#include "../lib/input.h"

using namespace std;

TEST(Stats, Mean){
    double x[] {-1.0, 1.0, -1.0, 1.0};
    ASSERT_DOUBLE_EQ(0.0, mean(x,4));
    double y[] {-1.0, 1.0, 2.0, 3.0};
    ASSERT_DOUBLE_EQ(1.25, mean(y,4));
}

TEST(StatsClass, Mean){
    Stats s = Stats();
    s.push(-1.0);
    s.push(1.0);
    s.push(-1.0);
    s.push(1.0);
    ASSERT_DOUBLE_EQ(0.0,s.getMean());
    Stats t = Stats();
    t.push(-1.0);
    t.push(1.0);
    t.push(2.0);
    t.push(3.0);
    ASSERT_DOUBLE_EQ(1.25, t.getMean());
}

TEST(Stats, Variance){
    double x[] {1.0};
    ASSERT_EQ(1, std::isnan(variance(x,1)));
    double y[] {1.0, 1.0, 1.0, 1.0};
    ASSERT_DOUBLE_EQ(0.0, variance(y,4));
    double z[] {-1, -1, 0, 1, 1};
    ASSERT_DOUBLE_EQ(1, variance(z,5));
}

TEST(StatsClass,Variance){
    Stats x,y,z;
    x.push(1.0);
    ASSERT_EQ(1, std::isnan(x.getVariance()));
    y.push(1.0);
    y.push(1.0);
    y.push(1.0);
    y.push(1.0);
    ASSERT_DOUBLE_EQ(0.0, y.getVariance());
    z.push(-1);
    z.push(-1);
    z.push(0);
    z.push(1);
    z.push(1);
    ASSERT_DOUBLE_EQ(1,z.getVariance());
}

TEST(Stats, Stdev){
    double x[] {1.0};
    ASSERT_EQ(1, std::isnan(stdev(x,1)));
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

TEST(Accumulate, valarray){
    std::valarray<double> v{1,2,3,4,5,6,7,8,9,10};
    ASSERT_DOUBLE_EQ(55,accumulate(v));
    ASSERT_DOUBLE_EQ(65,accumulate(v,10.));
    ASSERT_DOUBLE_EQ(0, accumulate(v,-55.));
}

TEST(Input, fname){
    ASSERT_STREQ("0.01-1e-06-100-1-0-0.dat", make_fname(variables{}).c_str());
}


TEST(Noise, Initialisation){
    Noise n{};
    ASSERT_NO_THROW(n.getVal());
    ASSERT_ANY_THROW(Noise{-1});
}

TEST(Noise, Distribution){
    Noise n{};
    Stats s{};
    double precision = 1e-2;
    long n_trials=2e5;
    for (long i=0; i!=n_trials; i++){
        s.push(n.getVal());
    }
    ASSERT_NEAR(0, s.getMean(), precision);
    ASSERT_NEAR(1, s.getStandardDeviation(), precision);
    ASSERT_NEAR(0, s.getSkewness(), precision);
}

TEST(Equation, FiniteDifference){
    Finite_Difference d{};
    valarray<double> v(1.,100);
    v = d.increment(v,1);
    ASSERT_DOUBLE_EQ(0, accumulate(v));
    valarray<double> small({1.,0});
    small = d.increment(small);
    ASSERT_DOUBLE_EQ(0, accumulate(small));
    valarray<double> tiny(1,1);
    tiny = d.increment(tiny);
    ASSERT_DOUBLE_EQ(0, accumulate(tiny));
}

TEST(Equation, FiniteDoubleDifference){
    Finite_Double_Difference d2{};
    valarray<double> v(1.,100);
    v = d2.increment(v);
    ASSERT_DOUBLE_EQ(0, accumulate(v));
    valarray<double> small({1.,0,1.});
    small = d2.increment(small);
    ASSERT_DOUBLE_EQ(0, accumulate(small));
    valarray<double> tiny{1,1};
    tiny = d2.increment(tiny);
    ASSERT_DOUBLE_EQ(0, accumulate(tiny));
}

TEST(Equation, Shear){
    Shear s{};
    ASSERT_DOUBLE_EQ(0, s.getA());
    ASSERT_DOUBLE_EQ(0, s.getD());
    ASSERT_DOUBLE_EQ(1, s.getQ());
    stringstream ss;
    ss << s;
    string string1 = ss.str();
    string string0 = "0 0 1";
    ASSERT_STREQ(string0.c_str(), string1.c_str());
    s = Shear{0,0,0};
    valarray<double> x{0.,100};
    x = s.increment(x, 1.);
    ASSERT_DOUBLE_EQ(0, accumulate(x));
    int iters = 100;
    double precision = 1e-3;
    s = Shear{};
    for (int i=0;i<iters;i++) x = s.increment(x, 1.);
    Stats st{x};
    ASSERT_NEAR(0, st.getMean(), precision);
}


TEST(Input, Blank){
}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
