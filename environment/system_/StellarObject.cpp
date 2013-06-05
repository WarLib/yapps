#include "StellarObject.hpp"
#include <cmath>
#include <OgreConfigFile.h>
#ifdef TESTING_ENV
#include <iostream>

using namespace std;
#endif

StellarObject::StellarObject(Ogre::Vector3 center, Ogre::Vector3 rot, double colonization) {
    _center = center;
    _rot = rot;
    _colonization = colonization;
    mConfigFile = "stellar.cfg";
}

const Ogre::Vector3& StellarObject::GetCenter(void) const {
    return _center;
}

const Ogre::Vector3& StellarObject::GetRotation(void) const {
    return _rot;
}

void StellarObject::SetDensity(double density) {
    _density = density;
}

void StellarObject::SetMass(double mass) {
    _mass = mass;
}

double StellarObject::GetRadius(void) {
    double vol = _mass / _density;
    double _r3 = vol / (4.0 / 3.0 * 3.14159);
    return pow(_r3, 1.0 / 3.0);
}

void StellarObject::ReadCfg(const Ogre::String& type, double& den, double& mass) {
    Ogre::ConfigFile cf;
    cf.load(mConfigFile);

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            if (secName.compare(type) == 0) {
#ifdef TESTING_ENV
                cout << secName << " - " << typeName << " - " << archName << endl;
#endif
                if (typeName.compare("avg_density") == 0) {
                    den = atof(archName.c_str());
                } else if (typeName.compare("avg_mass") == 0) {
                    mass = atof(archName.c_str());
                }
            }
        }
    }
}