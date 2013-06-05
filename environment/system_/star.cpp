#include "star.hpp"
#include "pred_random.hpp"

#ifdef TESTING_ENV
#include <iostream>

using namespace std;
#endif

const Ogre::String ThisType = "stars";

Star::Star(Ogre::Vector3 center, Ogre::Vector3 rot) : StellarObject(center, rot, 0) {
    double den, mass;
    Random & RANDGEN(Random::Instance());
    ReadCfg(ThisType, den, mass);
    double rand = RANDGEN.exponential();
    while (rand < 0.7) {
        rand += 0.13;
    }
    while (rand > 1.3) {
        rand -= 0.13;
    }

    _density = rand*den;
    rand = RANDGEN.exponential();
    while (rand < 0.7) {
        rand += 0.13;
    }
    while (rand > 1.3) {
        rand -= 0.13;
    }

    _mass = rand*mass;
}

void Star::Update() {
}
