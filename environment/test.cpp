#include <iostream>
#include "world.hpp"
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    Random & tmp(Random::Instance());
    int n = 1000;
    string seed;
    if (argc == 3) {
        n = atoi(argv[1]);
        seed = string(argv[2]);
    } else {
        seed = "magicrootseed";
    }
    Galaxy & MyGalaxy(Galaxy::GetGalaxy(n, 8,seed,true));
    return 0;
}
