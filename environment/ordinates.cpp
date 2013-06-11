#include "ordinates.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace Yapps;

Vec3::Vec3(const Ogre::Real fX, const Ogre::Real fY, const Ogre::Real fZ) : Ogre::Vector3(fX, fY, fZ) {
    _global.x = 0;
    _global.y = 0;
    _global.z = 0;
    gridify();
}

Vec3::Vec3() : Vector3(0, 0, 0) {
    _global.x = 0;
    _global.y = 0;
    _global.z = 0;
};

Vec3::Vec3(const lint gX, const lint gY, const lint gZ, const Ogre::Real fX, const Ogre::Real fY, const Ogre::Real fZ) : Ogre::Vector3(fX, fY, fZ) {
    _global.x = gX;
    _global.y = gY;
    _global.z = gZ;
    gridify();
}

Vec3::Vec3(const lint agCoordinate[3], const Ogre::Real afCoordinate[3]) : Ogre::Vector3(afCoordinate) {
    _global.x = agCoordinate[0];
    _global.y = agCoordinate[1];
    _global.z = agCoordinate[2];
    gridify();
}

Vec3::Vec3(grid_vec global, const Ogre::Real fX, const Ogre::Real fY, const Ogre::Real fZ) : Ogre::Vector3(fX, fY, fZ) {
    _global = global;
    gridify();
}

Vec3::Vec3(const lint agCoordinate[3], const int afCoordinate[3]) : Ogre::Vector3(afCoordinate) {
    _global.x = agCoordinate[0];
    _global.y = agCoordinate[1];
    _global.z = agCoordinate[2];
    gridify();
}

Vec3::Vec3(lint * const g, Ogre::Real * const r) : Ogre::Vector3(r) {
    _global.x = g[0];
    _global.y = g[1];
    _global.z = g[2];
    gridify();
}

Vec3::Vec3(const lint gscaler, const Ogre::Real scaler) : Ogre::Vector3(scaler) {
    _global.x = gscaler;
    _global.y = gscaler;
    _global.z = gscaler;
    gridify();
}

void Vec3::operator +=(const Vec3 & vgl) {
    _global.x += vgl._global.x;
    _global.y += vgl._global.y;
    _global.z += vgl._global.z;
    x += vgl.x;
    y += vgl.y;
    z += vgl.z;
    gridify();
}

Vec3 Vec3::operator +(const Vec3 & vgl) const {
    grid_vec tmp;
    tmp.x = _global.x + vgl._global.x;
    tmp.y = _global.y + vgl._global.y;
    tmp.z = _global.z + vgl._global.z;
    return Vec3(tmp, x + vgl.x, y + vgl.y, z + vgl.z);
}

void Vec3::operator -=(const Vec3 & vgl) {
    _global.x -= vgl._global.x;
    _global.y -= vgl._global.y;
    _global.z -= vgl._global.z;
    x -= vgl.x;
    y -= vgl.y;
    z -= vgl.z;
    gridify();
}

Vec3 Vec3::operator -(const Vec3 & vgl) const {
    grid_vec tmp;
    tmp.x = _global.x - vgl._global.x;
    tmp.y = _global.y - vgl._global.y;
    tmp.z = _global.z - vgl._global.z;
    return Vec3(tmp, x - vgl.x, y - vgl.y, z - vgl.z);
}

void Vec3::operator +=(const grid_vec & vgl) {
    _global.x += vgl.x;
    _global.y += vgl.y;
    _global.z += vgl.z;
}

Vec3 Vec3::operator +(const grid_vec & vgl) const {
    grid_vec tmp;
    tmp.x = _global.x + vgl.x;
    tmp.y = _global.y + vgl.y;
    tmp.z = _global.z + vgl.z;
    return Vec3(tmp, x, y, z);
}

void Vec3::operator -=(const grid_vec & vgl) {
    _global.x -= vgl.x;
    _global.y -= vgl.y;
    _global.z -= vgl.z;
}

Vec3 Vec3::operator -(const grid_vec & vgl) const {
    grid_vec tmp;
    tmp.x = _global.x - vgl.x;
    tmp.y = _global.y - vgl.y;
    tmp.z = _global.z - vgl.z;
    return Vec3(tmp, x, y, z);
}

void Vec3::operator *=(double val) {
    this->Vector3::operator *=(val);
    gridify();
}

void Vec3::operator *=(Vec3 val) {
    if (_global.x == 0 && _global.y == 0 && _global.z == 0) {
        this->Vector3::operator *=(val);
        gridify();
    } else {
        double tmp_x = (_global.x * GRID_UNIT + x) * val.x;
        double tmp_y = (_global.y * GRID_UNIT + y) * val.y;
        double tmp_z = (_global.z * GRID_UNIT + z) * val.z;
        _global.x = 0;
        _global.y = 0;
        _global.z = 0;

        x = tmp_x;
        y = tmp_y;
        z = tmp_z;
        gridify();
    }
}

Vec3 & Vec3::operator =(const Vec3& vgl) {
    _global.x = vgl._global.x;
    _global.y = vgl._global.y;
    _global.z = vgl._global.z;
    x = vgl.x;
    y = vgl.y;
    z = vgl.z;

    return *this;

}

bool Vec3::operator ==(const Vec3& vgl) const {
    return _global.x == vgl._global.x && _global.y == vgl._global.y && _global.z == vgl._global.z && this->Ogre::Vector3::operator ==(vgl);
}

bool Vec3::operator !=(const Vec3& vgl) const {
    return !(*this == vgl);

}

void Vec3::getAdjectant(grid_vec vector[26]) {
    int offset = 0;
    for (int i = 0; i < 27; i++) {
        lint x, y, z;
        if (i == 14)
            offset = 1;

        //y
        y = _global.y + (i / 9) - 1;

        //x
        x = _global.x + (i % 3) - 1;

        //z
        z = _global.z + (i / 3) % 3 - 1;

        vector[i - offset].x = x;
        vector[i - offset].y = y;
        vector[i - offset].z = z;
    }
}

void Vec3::gridify(void) {
    lint tmp_x, tmp_y, tmp_z;
    tmp_x = (lint) (x / GRID_UNIT);
    tmp_y = (lint) (y / GRID_UNIT);
    tmp_z = (lint) (z / GRID_UNIT);
    x -= tmp_x * GRID_UNIT;
    y -= tmp_y * GRID_UNIT;
    z -= tmp_z * GRID_UNIT;

    _global.x += tmp_x;
    _global.y += tmp_y;
    _global.z += tmp_z;

}

double Vec3::LocalDistance(const Vec3& vgl) const {
    return (*this).distance(vgl);
}

double Vec3::GlobalDistance(const Vec3& vgl) const {
    Vec3 tmp(0, 0, 0, x, y, z);
    Vec3 tmp2(vgl._global.x - _global.x, vgl._global.y - _global.y, vgl._global.z - _global.z, vgl.x, vgl.y, vgl.z);
    return (tmp - tmp2).GlobalLength();
}

double Vec3::LocalLength(void) const {
    return length();
}

double Vec3::GlobalLength(void) const {
    return sqrt(pow((double)_global.x * GRID_UNIT + x, (double)2.0) + pow((double)_global.y * GRID_UNIT + y, (double)2.0) + pow((double)_global.z * GRID_UNIT + z, (double)2.0));
}

double Vec3::AngleToGlobal(const Vec3& vgl) const {
    double nenner = GlobalLength() * vgl.GlobalLength();
    double zaehler = (_global.x * GRID_UNIT + x) * (vgl._global.x * GRID_UNIT + vgl.x)
            + (_global.y * GRID_UNIT + y) * (vgl._global.y * GRID_UNIT + vgl.y)
            + (_global.z * GRID_UNIT + z) * (vgl._global.z * GRID_UNIT + vgl.z);
    // Divide by zero check
    if (nenner < 1e-6f)
        nenner = 1e-6f;

    double f = zaehler / nenner;

    return Ogre::Math::ACos(f).valueRadians();
}

double Vec3::AngleToLocal(const Vec3& vgl) {
    return angleBetween(vgl).valueRadians();
}


// OLD STUFF
/*
Ordinate::Ordinate() {
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
}

Ordinate::Ordinate(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;
}

double Ordinate::GetOrdinates(ord index) {
    switch (index) {
        case X:
            return _x;
        case Y:
            return _y;
        case Z:
            return _z;
        default:
            return 0;
    }
}

double Ordinate::Value() const {
    double iRet;
    iRet = sqrt(pow(_x, 2.0) + pow(_y, 2.0) + pow(_z, 2.0));
    return iRet;
}

double Ordinate::Distance(const Ordinate& vgl) const {
    return ((*this) - vgl).Value();
}

bool Ordinate::operator<(const Ordinate& vgl) const {
    return this->Value() < vgl.Value();
}

Ordinate Ordinate::operator-(const Ordinate& vgl) const {
    return Ordinate(_x - vgl._x, _y - vgl._y, _z - vgl._z);
}

void Ordinate::operator*=(double val) {
    _x *= val;
    _y *= val;
    _z *= val;
}

Ordinate Ordinate::operator*(double val) const {
    //
    return Ordinate(_x * val, _y * val, _z * val);
}
 *
 * */
