#ifndef _ASTEROID_HPP
#define _ASTEROID_HPP

#include "StellarObject.hpp"

class Asteroid: public StellarObject {
protected:
public:
	Asteroid(Vec3 center, Ogre::Vector3 rot, Ogre::String name);
	void Update();
};

#endif