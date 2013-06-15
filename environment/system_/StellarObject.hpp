#ifndef _STELLAROBJECT_HPP
#define _STELLAROBJECT_HPP

#include <OgreVector3.h>
#include <OgreString.h>
#include "ordinates.hpp"

using namespace Yapps;

class StellarObject {
protected:
	Vec3 _center;
	Ogre::Vector3 _rot;
	double _colonization;

	Ogre::String _mesh;

	double _mass;
	double _density;
        Ogre::String mConfigFile;
        
        void ReadCfg(const Ogre::String& type, double& den, double& mass);
public:
	StellarObject(Vec3 center, Ogre::Vector3 rot, double colonization);
	virtual void Update() = 0;
	Vec3& GetCenter(void);
	const Ogre::Vector3& GetRotation(void) const;

	Ogre::String GetMeshName(void);

	void SetDensity(double density);
	void SetMass(double mass);

	double GetRadius(void);
};

#endif