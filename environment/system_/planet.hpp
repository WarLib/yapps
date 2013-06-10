#ifndef _PLANET_HPP
#define _PLANET_HPP

#include "StellarObject.hpp"

class Planet: public StellarObject {
protected:
public:
	Planet(Vec3 center, Ogre::Vector3 rot);
	void Update();
};

#endif