#include "Asteroid.hpp"
#include "pred_random.hpp"

const Ogre::String ThisType = "asteroids";

Asteroid::Asteroid(Vec3 center, Ogre::Vector3 rot) : StellarObject(center, rot, 0) {
	cout << "New Asteroid at " << center << endl;
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

	_mesh = "asteroid_high.mesh";

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

void Asteroid::Update() {
}
