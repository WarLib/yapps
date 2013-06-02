#ifndef _PREDRANDOM_HPP
#define _PREDRANDOM_HPP

#include <string>

typedef unsigned long ulong;

using namespace std;

#define PI 3.14159265359


//predictable random generator

class Random {
private:
    static Random _instance;
    unsigned char* _s;
    int _i, _j;
    ulong _min,_max;

    Random();
    Random(const Random&);
    ulong _seed;

    void swap(int i, int j);
    void mix(const string& seed);
    unsigned char nextByte(void);

public:

    static Random& Instance(void);

    ~Random() {
        delete[] _s;
    };

    void init(const string& seed);
    //void init(ulong seed);

    string MakeSeed();

    ulong next(void);
    int NextSign(void);
    ulong GetMax(void);
    void SetMax(ulong max);

    double uniform(void);
    ulong random(ulong n = 0, ulong m = 0);
    double normal(void);
    double exponential(void);
    ulong poisson(double mean);
    double gamma(double a);
};

#endif