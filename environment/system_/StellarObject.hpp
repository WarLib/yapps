#ifndef _STELLAROBJECT_HPP
#define _STELLAROBJECT_HPP

#include <OgreVector3.h>
#include <OgreString.h>

class StellarObject {
protected:
	Ogre::Vector3 _center;
	Ogre::Vector3 _rot;
	double _colonization;

	double _mass;
	double _density;
        Ogre::String mConfigFile;
        
        void ReadCfg(const Ogre::String& type, double& den, double& mass);
public:
	StellarObject(Ogre::Vector3 center, Ogre::Vector3 rot, double colonization);
	virtual void Update() = 0;
	const Ogre::Vector3& GetCenter(void) const;
	const Ogre::Vector3& GetRotation(void) const;

	void SetDensity(double density);
	void SetMass(double mass);

	double GetRadius(void);
};

#endif