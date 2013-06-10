#ifndef _GIANTS_HPP
#define _GIANTS_HPP
#include "StellarObject.hpp"

class Giant: public StellarObject {
protected:
public:
	Giant(Vec3 center, Ogre::Vector3 rot);
	void Update();
};

#endif