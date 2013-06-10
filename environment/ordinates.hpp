#ifndef _ORDINATES_HPP
#define _ORDINATES_HPP

#include <OgreVector3.h>

typedef long int lint;

#define METER 1e-10lf;
namespace Yapps {

    enum ord {
        X, Y, Z
    };

    class Vec3 : public Ogre::Vector3 {
    protected:
        long int _g_x, _g_y, _g_z;
    public:
        Vec3();
        Vec3(const lint gX, const lint gY, const lint gZ, const Ogre::Real fX, const Ogre::Real fY, const Ogre::Real fZ);
        Vec3(const lint agCoordinate[3], const Ogre::Real afCoordinate[3]);
        Vec3(const lint agCoordinate[3], const int afCoordinate[3]);
        Vec3(lint * const g, Ogre::Real * const r);
        Vec3(const lint gscaler, const Ogre::Real scaler);
    };
};

class Ordinate {
protected:
    double _x;
    double _y;
    double _z;
public:
    Ordinate();
    Ordinate(double x, double y, double z);
    double GetOrdinates(Yapps::ord index);
    double Value(void) const;
    double Distance(const Ordinate& vgl) const;

    bool operator<(const Ordinate& vgl) const;
    Ordinate operator-(const Ordinate& vgl) const;
    void operator*=(double val);
    Ordinate operator*(double val) const;
};

#endif
