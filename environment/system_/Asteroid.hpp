#ifndef _ASTEROID_HPP
#define _ASTEROID_HPP

#include "StellarObject.hpp"

class Asteroid: public StellarObject {
protected:
public:
	Asteroid(Ogre::Vector3 center, Ogre::Vector3 rot);
	void Update();
};

#endif