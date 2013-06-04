#ifndef _STAR_HPP
#define _STAR_HPP
#include "StellarObject.hpp"

class Star: public StellarObject {
protected:
public:
	Star(Ogre::Vector3 center, Ogre::Vector3 rot);
	void Update();
};

#endif