#include <gtest/gtest.h>
#include <sstream>
#include "../lib/noise.h"
#include "../lib/functions.h"
#include "../lib/differentiate.h"
#include "../lib/noise.h"
#include "../lib/Equation.h"
#include "../lib/input.h"
#include "../lib/Search.h"

using namespace std;

void printValArray(valarray<double> r){
    for (auto i=0; i<r.size(); i++){
        cout << r[i] << " ";
    }
    cout << endl;
}

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
    double precision = 2e-2;
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
    variables v{};
    Shear s{v};
    ASSERT_DOUBLE_EQ(0, s.getA());
    ASSERT_DOUBLE_EQ(0, s.getD());
    ASSERT_DOUBLE_EQ(1, s.getQ());
    stringstream ss;
    ss << s;
    string string1 = ss.str();
    string string0 = "0 0 1 100 0.01 1e-06 0";
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
    //ASSERT_NEAR(0, st.getMean(), precision);
}

TEST(Euler, DefaultConstructor){
    Euler e{};
    variables v{};
    ASSERT_DOUBLE_EQ(v.total_time, e.getTotalTime());
    ASSERT_DOUBLE_EQ(v.size, e.getSize());
    ASSERT_DOUBLE_EQ(v.dt, e.getTimestep());
}

TEST(Euler, Output){
    Euler e{};
    ASSERT_DOUBLE_EQ(1e-6, e.getTimestep());
    stringstream ss;
    ss << e;
    string string1 = ss.str();
    string string0 = "100 0.01 1e-06 0";
    ASSERT_STREQ(string0.c_str(), string1.c_str());
}


TEST(Euler, Outfile){
    Euler e{};
    ASSERT_STREQ(make_fname(variables{}).c_str(), e.getFname().c_str());
    ifstream f{e.getFname()};
    string s;
    getline(f,s);
    ASSERT_STREQ("Xpos Height Time", s.c_str());

}

TEST(Euler, VariableConstructor){
    variables v{};
    v.total_time = 1;
    v.dt = 1e-8;
    Euler e{v};
    ASSERT_DOUBLE_EQ(v.total_time, e.getTotalTime());
    ASSERT_DOUBLE_EQ(v.size, e.getSize());
    ASSERT_DOUBLE_EQ(v.dt, e.getTimestep());
}


TEST(Euler, Step){
    variables v{};
    v.dt = 1;
    v.total_time = 1;
    v.delta = 1;
    v.Q = 0;
    Shear s{v};
    Euler e{v};
    valarray<double> r = s.increment(valarray<double>(0.,e.getSize()), e.getTimestep());
    e.step(s);
    ASSERT_DOUBLE_EQ(1, accumulate(r)/r.size());
    ASSERT_DOUBLE_EQ(1, e.getCharVal());
}

TEST(Input, Blank){
}

TEST(BinarySearch, Null){
    Binary_Search bs{};
    double v = bs.getVal(0, 0);
    ASSERT_DOUBLE_EQ(0, v);
}

TEST(BinarySearch, Above){
    Binary_Search bs{};
    double v = bs.getVal(0, 1);
    ASSERT_DOUBLE_EQ(-0.1, v);
}

TEST(BinarySearch, Below){
    Binary_Search bs{};
    double v = bs.getVal(0, -1);
    ASSERT_DOUBLE_EQ(0.1, v);
}

TEST(BinarySearch, LargeDelta){
    Binary_Search bs{1};
    double v = bs.getVal(0, -1);
    ASSERT_DOUBLE_EQ(1, v);
}

TEST(BinarySearch, Search){
    Binary_Search bs1{1};
    double val = 5;
    double v = 0;
    while (val != v){
        v = val;
        val = bs1.getVal(val, int(val));
    }
    ASSERT_DOUBLE_EQ(0, v);
    Binary_Search bs2{1};
    val = -5;
    v = 0;
    while (val != v){
        v = val;
        val = bs2.getVal(val, int(val));
    };
    ASSERT_DOUBLE_EQ(0, v);
}

TEST(BinarySearch, Iterations){
    Binary_Search bs{};
    while (!bs.done()){
        bs.getVal(1,1);
    }
    ASSERT_EQ(101,bs.numIters());
}

TEST(BinarySearch, Function){
    Binary_Search bs{};
    double val = 1.2;
    while (!bs.done()){
        val = bs.getVal(tan(val), tan(val) < 0 ? -1 : 1);
    }
    ASSERT_NEAR(0, tan(val), 1e-5);
}

TEST(Shear, DefaultConstructor){
    Shear s{};
    ASSERT_DOUBLE_EQ(0, s.getA());
    ASSERT_DOUBLE_EQ(0, s.getD());
    ASSERT_DOUBLE_EQ(1, s.getQ());
    ASSERT_DOUBLE_EQ(0.01, s.getTotalTime());
    ASSERT_DOUBLE_EQ(1e-6, s.getTimestep());
    ASSERT_EQ(100, s.getSize());
}

TEST(Shear, Rand){
    Shear s{};
    size_t size{100};
    valarray<double> x(size);
    for (int i=0; i<size; i++){
        x[i] = s.getRand();
    }
    ASSERT_NE(0, accumulate(x));
}

TEST(Shear, Output){
    Shear s{};
    ASSERT_DOUBLE_EQ(1e-6, s.getTimestep());
    stringstream ss;
    ss << s;
    string string1 = ss.str();
    string string0 = "0 0 1 100 0.01 1e-06 0";
    ASSERT_STREQ(string0.c_str(), string1.c_str());
}

TEST(Shear, IntegratedOutput){
    variables v{};
    v.delta = 1;
    v.Q = 0;
    Shear s{v};
    s.solve();
    stringstream ss;
    ss << s;
    string str1 = ss.str();
    string str0 = "0 1 0 100 0.01 1e-06 0.005";
    ASSERT_NEAR(0.005, s.getCharVal(), 1e-7);
    ASSERT_STREQ(str0.c_str(), str1.c_str());
}

TEST(Shear, Increment){
    Shear s{0, 1, 0};
    valarray<double> r = s.increment(valarray<double>(0., 10), 1);
    ASSERT_DOUBLE_EQ(10, accumulate(r));
}

TEST(Shear, IncrementRand){
    Shear s{};
    valarray<double> r = s.increment(valarray<double>(0., 10), 1);
    ASSERT_NE(0., accumulate(r));
}

TEST(Shear, IntegrateManual){
    int steps = 10;
    valarray<double> x(0.,10);
    Shear s{};
    for (auto i=0; i<steps;i++){
        x += s.increment(x,0.01);
    }
    ASSERT_NE(0., accumulate(x));
}

TEST(Shear, IntegrateSimple){
    variables v{};
    v.delta = 1;
    v.Q = 0;
    Shear s{v};
    s.Integrate();
    ASSERT_NEAR(0.005, s.getCharVal(), 1e-6);
}

TEST(Shear, Integrate){
    Shear s1{};
    double r1 = s1.Integrate();
    Shear s2{0,1};
    double r2 = s2.Integrate();
    ASSERT_GT(r2, r1);
}

TEST(Shear, SearchSimple){
    variables v{};
    v.run_search = 1;
    v.delta = 0.5;
    Shear s{v};
    s.solve();
    ASSERT_NEAR(0, s.getCharVal(), 2e-4);
}

TEST(Shear, Search){
    variables v{};
    v.run_search = 1;
    v.delta = 0.5;
    v.A = 0.2;
    Shear s{v};
    s.solve();
    ASSERT_NEAR(0, s.getCharVal(), 2e-4);
}


TEST(Values, Positive){
    variables v{};
    v.total_time = 0.01;
    v.dt = 1e-7;
    v.Q = 1;
    vector<double> As{0.01, 0.1};
    vector<double> Ds{0.5, 1, 1.5, 3};

    for (auto A: As){
        for (auto D: Ds){
            v.A = A;
            v.delta = D;
            Shear s{v};
            s.solve();
            ASSERT_TRUE(s.getCharVal() > 0);
        }
    }
}


TEST(Values, Negative){
    variables v{};
    v.total_time = 0.01;
    v.dt = 1e-7;
    v.Q = 1;
    vector<double> As{0.5, 1, 1.5, 3};
    vector<double> Ds{0, 0.1};

    for (auto A: As){
        for (auto D: Ds){
            v.A = A;
            v.delta = D;
            Shear s{v};
            s.solve();
            ASSERT_TRUE(s.getCharVal() < 0);
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
    ASSERT_NEAR(r1, r2, precision);
    ASSERT_NEAR(r2, r4, precision);
    ASSERT_NEAR(r1, r3, precision);
    ASSERT_NEAR(r3, r4, precision);

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
    vector<int> sizes{100, 200};
    vector<double> timesteps{1e-6, 5e-7, 1e-7};
    vector<double> times{1, 0.1, 0.01};
    for (auto size: sizes){
        for (auto timestep: timesteps){
            for (auto time: times){
                v.size = size;
                v.dt = timestep;
                v.total_time = time;
                Shear s{v};
                s.solve();
                double d = s.getD();
                ASSERT_NEAR(d1, d, precision);
            }
        }
    }
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
