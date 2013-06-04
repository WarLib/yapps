#include "StellarObject.hpp"
#include <cmath>

StellarObject::StellarObject(Ogre::Vector3 center, Ogre::Vector3 rot, double colonization) {
	_center = center;
	_rot = rot;
	_colonization = colonization;
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
	//masse = dichte * volumen
	//volumen = 4/3*pi*r³
	//r³ = Volumen / ( 4/3 * pi)
	//Volumen = masse / dichte;
	double vol = _mass / _density;
	double _r3 = vol / (4.0/3.0 * 3.14159);
	return pow(_r3,1.0/3.0);
}