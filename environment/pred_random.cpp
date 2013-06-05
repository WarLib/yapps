#include "pred_random.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>

#ifdef TESTING_ENV
#include <iostream>
#endif

using namespace std;


//Helpers



//Class Random
Random Random::_instance = Random();

Random& Random::Instance(void) {
    return Random::_instance;
}

Random::Random() {
    _min = 0; 
    _max = 5000000;
}

string Random::MakeSeed() {
    stringstream seed;
    unlong tmp;
    srand(time(0));
    tmp = rand();
    seed << tmp;
    init(seed.str());
    return seed.str();
}

int Random::NextSign(void) {
    double tmp = normal();
    int tmp2 = int(tmp <= 0);
    if (tmp2 == 0)
        tmp2 = -1;
    return tmp2;
}

unlong Random::GetMax(void) {
    return _max;
}

void Random::SetMax(unlong max) {
    _max = max;
}

void Random::init(const string& seed) {
#ifdef TESTING_ENV
    cout << "initializing generator with a seed" << endl;
#endif
    _s = new unsigned char[256];
    _i = 0;
    _j = 0;
    for (int i = 0; i < 256; i++) {
        _s[i] = i;
    }
    if (seed.length() != 0) {
        mix(seed);
    }
}

void Random::swap(int i, int j) {
    unsigned char tmp = _s[i];
    _s[i] = _s[j];
    _s[j] = tmp;
};

void Random::mix(const string &seed) {
    unsigned char* input = (unsigned char*) seed.c_str();
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j += _s[i] + input[i % seed.length()];
        j %= 256;
        swap(i, j);
    }
};

unsigned char Random::nextByte(void) {
    _i = (_i + 1) % 256;
    _j = (_j + _s[_i]) % 256;
    swap(_i, _j);
    return _s[(_s[_i] + _s[_j]) % 256];
};

double Random::uniform() {
    int BYTES = 7; // 56 bits to make a 53-bit double
    double output = 0;
    for (int i = 0; i < BYTES; i++) {
        output *= 256;
        output += nextByte();
    }
    return output / (pow(2, (double)BYTES * 8) - 1);
};

unlong Random::random(unlong n, unlong m) {
    if (m == 0 && n == 0) {
        n = _min;
        m = _max;
    }
    return n + (unlong) (uniform() * (m - n));
};

double Random::normal(void) {
    double x = uniform(); // can't be exactly 0
    double y = uniform();
    return sqrt((double)-2 * log(x)) * cos((double)2 * MYPI * (double)y);
};

double Random::exponential(void) {
    return -log(uniform());
};

unlong Random::poisson(double mean) {
    double L = exp(-(mean));
    unlong k = 0;
    double p = 1;
    do {
        k++;
        p *= uniform();
    } while (p > L);
    return k - 1;
};

double Random::gamma(double a) {
    double d = (a < 1 ? 1 + a : a) - 1 / 3;
    double c = 1 / sqrt(9 * d);
    double v;
    double u;
    double x2;
    double x;
    do {
        do {
            x = normal();
            v = pow(c * x + 1, 3);
        } while (v <= 0);
        u = uniform();
        x2 = pow(x, 2);
    } while (u >= 1 - 0.0331 * x2 * x2 &&
            log(u) >= 0.5 * x2 + d * (1 - v + log(v)));
    if (a < 1) {
        return d * v * exp(exponential() / -a);
    } else {
        return d * v;
    }
};