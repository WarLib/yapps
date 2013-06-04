#ifndef _PREDRANDOM_HPP
#define _PREDRANDOM_HPP

#include <string>

typedef unsigned long unlong;

using namespace std;

#define MYPI 3.14159265359


//predictable random generator

class Random {
private:
    static Random _instance;
    unsigned char* _s;
    int _i, _j;
    unlong _min,_max;

    Random();
    Random(const Random&);
    unlong _seed;

    void swap(int i, int j);
    void mix(const string& seed);
    unsigned char nextByte(void);

public:

    static Random& Instance(void);

    ~Random() {
        delete[] _s;
    };

    void init(const string& seed);
    //void init(unlong seed);

    string MakeSeed();

    unlong next(void);
    int NextSign(void);
    unlong GetMax(void);
    void SetMax(unlong max);

    double uniform(void);
    unlong random(unlong n = 0, unlong m = 0);
    double normal(void);
    double exponential(void);
    unlong poisson(double mean);
    double gamma(double a);
};

#endif