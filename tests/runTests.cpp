#include <gtest/gtest.h>
#include <sstream>
#include "../lib/noise.h"
#include "../lib/functions.h"
#include "../lib/noise.h"
#include "../lib/Equation.h"
#include "../lib/input.h"
#include "../lib/Search.h"

void printValArray(std::valarray<double> r){
    for (auto i=0; i<r.size(); i++){
        std::cout << r[i] << " ";
    }
    std::cout << std::endl;
}

TEST(Stats, Mean){
    double x[] {-1.0, 1.0, -1.0, 1.0};
    EXPECT_DOUBLE_EQ(0.0, mean(x,4));
    double y[] {-1.0, 1.0, 2.0, 3.0};
    EXPECT_DOUBLE_EQ(1.25, mean(y,4));
}

TEST(Stats, Variance){
    double x[] {1.0};
    EXPECT_EQ(1, std::isnan(variance(x,1)));
    double y[] {1.0, 1.0, 1.0, 1.0};
    EXPECT_DOUBLE_EQ(0.0, variance(y,4));
    double z[] {-1, -1, 0, 1, 1};
    EXPECT_DOUBLE_EQ(1, variance(z,5));
}

TEST(Stats, Stdev){
    double x[] {1.0};
    EXPECT_EQ(1, std::isnan(stdev(x,1)));
    double y[] {1.0, 1.0, 1.0, 1.0};
    EXPECT_DOUBLE_EQ(0.0, stdev(y,4));
    double z[] {-1, -1, 0, 1, 1};
    EXPECT_DOUBLE_EQ(1, stdev(z,5));
}

TEST(Stats, Sum){
    double x[] {1,2,3,4};
    EXPECT_DOUBLE_EQ(10, sum(x,4));
    double y[] {-1,-2,1,2};
    EXPECT_DOUBLE_EQ(0, sum(y,4));
    double z[] {-1,-2,-3,-4};
    EXPECT_DOUBLE_EQ(-10, sum(z,4));
}

TEST(Accumulate, valarray){
    std::valarray<double> v{1,2,3,4,5,6,7,8,9,10};
    EXPECT_DOUBLE_EQ(55,accumulate(v));
    EXPECT_DOUBLE_EQ(65,accumulate(v,10.));
    EXPECT_DOUBLE_EQ(0, accumulate(v,-55.));
}

TEST(Input, fname){
    EXPECT_STREQ("0.01-1e-06-100-1-0-0.dat", make_fname(variables{}).c_str());
}


TEST(Noise, Initialisation){
    Noise n{};
    EXPECT_NO_THROW(n.getVal());
    EXPECT_ANY_THROW(Noise{-1});
}

TEST(Noise, Distribution){
    Noise n{};
    Stats::Stats s{};
    double precision = 2e-2;
    long n_trials=2e5;
    for (long i=0; i!=n_trials; i++){
        s.push(n.getVal());
    }
    EXPECT_NEAR(0, s.getMean(), precision);
    EXPECT_NEAR(1, s.getStandardDeviation(), precision);
    EXPECT_NEAR(0, s.getSkewness(), precision);
}

TEST(Equation, FiniteDifference){
    Finite_Difference d{};
    std::valarray<double> v(1.,100);
    v = d.increment(v,1);
    EXPECT_DOUBLE_EQ(0, accumulate(v));
    std::valarray<double> small({1.,0});
    small = d.increment(small);
    EXPECT_DOUBLE_EQ(0, accumulate(small));
    std::valarray<double> tiny(1,1);
    tiny = d.increment(tiny);
    EXPECT_DOUBLE_EQ(0, accumulate(tiny));
}

TEST(Equation, FiniteDoubleDifference){
    Finite_Double_Difference d2{};
    std::valarray<double> v(1.,100);
    v = d2.increment(v);
    EXPECT_DOUBLE_EQ(0, accumulate(v));
    std::valarray<double> small({1.,0,1.});
    small = d2.increment(small);
    EXPECT_DOUBLE_EQ(0, accumulate(small));
    std::valarray<double> tiny{1,1};
    tiny = d2.increment(tiny);
    EXPECT_DOUBLE_EQ(0, accumulate(tiny));
}

TEST(Equation, Shear){
    variables v{};
    Shear s{v};
    EXPECT_DOUBLE_EQ(0, s.getA());
    EXPECT_DOUBLE_EQ(0, s.getD());
    EXPECT_DOUBLE_EQ(1, s.getQ());
    std::stringstream ss;
    ss << s;
    std::string string1 = ss.str();
    std::string string0 = "0 0 1 100 0.01 1e-06 0";
    EXPECT_STREQ(string0.c_str(), string1.c_str());
    Shear s2{0,0,0};
    std::valarray<double> x{0.,100};
    x = s2.increment(x, 1.);
    EXPECT_DOUBLE_EQ(0, accumulate(x));
    int iters = 100;
    double precision = 1e-3;
    Shear s3{};
    for (int i=0;i<iters;i++) x = s3.increment(x, 1.);
    EXPECT_NEAR(0, s3.getCharVal(), precision);
}

TEST(Euler, DefaultConstructor){
    Euler e{};
    variables v{};
    EXPECT_DOUBLE_EQ(v.total_time, e.getTotalTime());
    EXPECT_DOUBLE_EQ(v.size, e.getSize());
    EXPECT_DOUBLE_EQ(v.dt, e.getTimestep());
}

TEST(Euler, Output){
    Euler e{};
    EXPECT_DOUBLE_EQ(1e-6, e.getTimestep());
    std::stringstream ss;
    ss << e;
    std::string string1 = ss.str();
    std::string string0 = "100 0.01 1e-06 0";
    EXPECT_STREQ(string0.c_str(), string1.c_str());
}


TEST(Euler, Outfile){
    Euler e{};
    EXPECT_STREQ(make_fname(variables{}).c_str(), e.getFname().c_str());
    std::ifstream f{e.getFname()};
    std::string s;
    getline(f,s);
    EXPECT_STREQ("Xpos Height Time", s.c_str());

}

TEST(Euler, VariableConstructor){
    variables v{};
    v.total_time = 1;
    v.dt = 1e-8;
    Euler e{v};
    EXPECT_DOUBLE_EQ(v.total_time, e.getTotalTime());
    EXPECT_DOUBLE_EQ(v.size, e.getSize());
    EXPECT_DOUBLE_EQ(v.dt, e.getTimestep());
}


TEST(Euler, Step){
    variables v{};
    v.dt = 1;
    v.total_time = 1;
    v.delta = 1;
    v.Q = 0;
    Shear s{v};
    Euler e{v};
    std::valarray<double> r = s.increment(std::valarray<double>(0.,e.getSize()), e.getTimestep());
    e.step(s);
    EXPECT_DOUBLE_EQ(1, accumulate(r)/r.size());
    EXPECT_DOUBLE_EQ(1, e.getCharVal());
}

TEST(Input, Blank){
}

TEST(BinarySearch, Null){
    Binary_Search bs{};
    double v = bs.getVal(0, 0);
    EXPECT_DOUBLE_EQ(0, v);
}

TEST(BinarySearch, Above){
    Binary_Search bs{};
    double v = bs.getVal(0, 1);
    EXPECT_DOUBLE_EQ(-0.1, v);
}

TEST(BinarySearch, Below){
    Binary_Search bs{};
    double v = bs.getVal(0, -1);
    EXPECT_DOUBLE_EQ(0.1, v);
}

TEST(BinarySearch, LargeDelta){
    Binary_Search bs{1};
    double v = bs.getVal(0, -1);
    EXPECT_DOUBLE_EQ(1, v);
}

TEST(BinarySearch, Search){
    Binary_Search bs1{1};
    double val = 5;
    double v = 0;
    while (val != v){
        v = val;
        val = bs1.getVal(val, int(val));
    }
    EXPECT_DOUBLE_EQ(0, v);
    Binary_Search bs2{1};
    val = -5;
    v = 0;
    while (val != v){
        v = val;
        val = bs2.getVal(val, int(val));
    };
    EXPECT_DOUBLE_EQ(0, v);
}

TEST(BinarySearch, Iterations){
    Binary_Search bs{};
    while (!bs.done()){
        bs.getVal(1,1);
    }
    EXPECT_EQ(101,bs.numIters());
}

TEST(BinarySearch, Function){
    Binary_Search bs{};
    double val = 1.2;
    while (!bs.done()){
        val = bs.getVal(tan(val), tan(val) < 0 ? -1 : 1);
    }
    EXPECT_NEAR(0, tan(val), 1e-5);
}

TEST(Shear, DefaultConstructor){
    Shear s{};
    EXPECT_DOUBLE_EQ(0, s.getA());
    EXPECT_DOUBLE_EQ(0, s.getD());
    EXPECT_DOUBLE_EQ(1, s.getQ());
    EXPECT_DOUBLE_EQ(0.01, s.getTotalTime());
    EXPECT_DOUBLE_EQ(1e-6, s.getTimestep());
    EXPECT_EQ(100, s.getSize());
}

TEST(Shear, Rand){
    Shear s{};
    size_t size{100};
    std::valarray<double> x(size);
    for (int i=0; i<size; i++){
        x[i] = s.getRand();
    }
    EXPECT_NE(0, accumulate(x));
}

TEST(Shear, Output){
    Shear s{};
    EXPECT_DOUBLE_EQ(1e-6, s.getTimestep());
    std::stringstream ss;
    ss << s;
    std::string string1 = ss.str();
    std::string string0 = "0 0 1 100 0.01 1e-06 0";
    EXPECT_STREQ(string0.c_str(), string1.c_str());
}

TEST(Shear, IntegratedOutput){
    variables v{};
    v.delta = 1;
    v.Q = 0;
    Shear s{v};
    s.solve();
    std::stringstream ss;
    ss << s;
    std::string str1 = ss.str();
    std::string str0 = "0 1 0 100 0.01 1e-06 0.01";
    EXPECT_NEAR(0.01, s.getCharVal(), 1e-7);
    EXPECT_STREQ(str0.c_str(), str1.c_str());
}

TEST(Shear, Increment){
    Shear s{0, 1, 0};
    std::valarray<double> r = s.increment(std::valarray<double>(0., 10), 1);
    EXPECT_DOUBLE_EQ(10, accumulate(r));
}

TEST(Shear, IncrementRand){
    Shear s{};
    std::valarray<double> r = s.increment(std::valarray<double>(0., 10), 1);
    EXPECT_NE(0., accumulate(r));
}

TEST(Shear, IntegrateManual){
    variables v{};
    int steps = 100;
    double dt = 0.01;
    std::valarray<double> x(0.,10);
    Shear s{0,1,0};
    for (auto i=0; i<steps;i++){
        x += s.increment(x,dt);
    }
    EXPECT_NE(0., accumulate(x));
    x -= dt*steps;
    EXPECT_NEAR(0, accumulate(x), 1e-14);
}

TEST(Shear, IntegrateSimple){
    variables v{};
    v.delta = 1;
    v.A = 0;
    v.Q = 0;
    v.dt = 0.001;
    v.total_time = 0.002;
    Shear s{v};
    s.Integrate();
    EXPECT_NEAR(v.total_time*v.delta, s.getCharVal(), 1e-6);
}

TEST(Shear, IntegrateVel){
    variables v{};
    v.delta = 1;
    v.A = 0;
    v.Q = 0;
    v.dt = 1e-6;
    v.total_time = 1e-3;
    Shear s{v};
    s.Integrate();
    EXPECT_NEAR(v.total_time*v.delta, s.getCharVal(), 1e-15);
}

TEST(Shear, Integrate){
    Shear s1{};
    double r1 = s1.Integrate();
    Shear s2{0,1};
    double r2 = s2.Integrate();
    EXPECT_GT(r2, r1);
}

TEST(Shear, SearchSimple){
    variables v{};
    v.run_search = 1;
    v.delta = 0.5;
    Shear s{v};
    s.solve();
    EXPECT_NEAR(0, s.getCharVal(), 2e-4);
}

TEST(Shear, Search){
    variables v{};
    v.run_search = 1;
    v.delta = 0.5;
    v.A = 0.2;
    Shear s{v};
    s.solve();
    EXPECT_NEAR(0, s.getCharVal(), 2e-4);
}


TEST(Values, Positive){
    variables v{};
    v.total_time = 0.01;
    v.dt = 1e-7;
    v.Q = 1;
    std::vector<double> As{0.01, 0.1};
    std::vector<double> Ds{0.5, 1, 1.5, 3};

    for (auto A: As){
        for (auto D: Ds){
            v.A = A;
            v.delta = D;
            Shear s{v};
            s.solve();
            EXPECT_TRUE(s.getCharVal() > 0);
        }
    }
}


TEST(Values, Negative){
    variables v{};
    v.total_time = 0.01;
    v.dt = 1e-7;
    v.Q = 1;
    std::vector<double> As{0.5, 1, 1.5, 3};
    std::vector<double> Ds{0, 0.1};

    for (auto A: As){
        for (auto D: Ds){
            v.A = A;
            v.delta = D;
            Shear s{v};
            s.solve();
            EXPECT_TRUE(s.getCharVal() < 0);
        }
    }
}

TEST(Scaling, ConstTime){
    variables v{};
    v.total_time = 0.1;
    v.A = 0.1;
    v.delta = 0.1;

    variables v1 = v;
    v1.dt = 1e-7;
    v1.size = 100;
    variables v2 = v;
    v2.dt = 5e-7;
    v2.size = 100;
    variables v3 = v;
    v3.dt = 1e-7;
    v3.size = 200;
    variables v4 = v;
    v4.dt = 5e-7;
    v4.size = 200;

    Shear s1{v1};
    Shear s2{v2};
    Shear s3{v3};
    Shear s4{v4};
    double r1 = s1.solve();
    double r2 = s2.solve();
    double r3 = s3.solve();
    double r4 = s4.solve();

    double precision = 1e-3;
    EXPECT_NEAR(r1, r2, precision);
    EXPECT_NEAR(r2, r4, precision);
    EXPECT_NEAR(r1, r3, precision);
    EXPECT_NEAR(r3, r4, precision);

}

TEST(Scaling, SteadyState){
    double precision = 5e-1;
    variables v{};
    v.run_search = 1;
    v.A = 1;
    v.delta = 0.3;
    Shear s1{v};
    s1.solve();
    double d1 = s1.getD();
    std::vector<int> sizes{100, 200};
    std::vector<double> timesteps{1e-6, 5e-7, 1e-7};
    std::vector<double> times{1, 0.1, 0.01};
    for (auto size: sizes){
        for (auto timestep: timesteps){
            for (auto time: times){
                v.size = size;
                v.dt = timestep;
                v.total_time = time;
                Shear s{v};
                s.solve();
                double d = s.getD();
                EXPECT_NEAR(d1, d, precision);
            }
        }
    }
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
