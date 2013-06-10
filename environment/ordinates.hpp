#ifndef _ORDINATES_HPP
#define _ORDINATES_HPP

#include <OgreVector3.h>

typedef long int lint;

#define METER 1e-3f
#define GRID_UNIT 1e+30f

namespace Yapps {

    typedef struct {
        lint x, y, z;
    } grid_vec;

    enum ord {
        X, Y, Z
    };

    class Vec3 : public Ogre::Vector3 {
    protected:
        grid_vec _global;
        void gridify(void);
    public:
        Vec3();
        Vec3(const Ogre::Real fX, const Ogre::Real fY, const Ogre::Real fZ);
        Vec3(const lint gX, const lint gY, const lint gZ, const Ogre::Real fX, const Ogre::Real fY, const Ogre::Real fZ);
        Vec3(const lint agCoordinate[3], const Ogre::Real afCoordinate[3]);
        Vec3(const lint agCoordinate[3], const int afCoordinate[3]);
        Vec3(grid_vec global, const Ogre::Real fX, const Ogre::Real fY, const Ogre::Real fZ);
        Vec3(lint * const g, Ogre::Real * const r);
        Vec3(const lint gscaler, const Ogre::Real scaler);

        void operator +=(const Vec3 & vgl);
        Vec3 operator +(const Vec3 & vgl) const;
        void operator -=(const Vec3 & vgl);
        Vec3 operator -(const Vec3 & vgl) const;

        void operator +=(const grid_vec & vgl);
        Vec3 operator +(const grid_vec & vgl) const;
        void operator -=(const grid_vec & vgl);
        Vec3 operator -(const grid_vec & vgl) const;

        void operator *=(double val);
        void operator *=(Vec3 val);


        Vec3 & operator =(const Vec3& vgl);

        bool operator ==(const Vec3& vgl) const;
        bool operator !=(const Vec3& vgl) const;

        void getAdjectant(grid_vec vector[26]);
        double LocalDistance(const Vec3& vgl) const;
        double GlobalDistance(const Vec3& vgl) const;
        double LocalLength(void) const;
        double GlobalLength(void) const;

        double AngleToGlobal(const Vec3& vgl) const;
        double AngleToLocal(const Vec3& vgl);
    };
};

/*
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
*/ 
#endif
