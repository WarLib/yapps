#include "ordinates.hpp"
#include <cmath>

using namespace Yapps;

Vec3::Vec3() : Vector3(0, 0, 0) {
    _g_x = 0;
    _g_y = 0;
    _g_z = 0;
};

Vec3::Vec3(const lint gX, const lint gY, const lint gZ, const Real fX, const Real fY, const Real fZ) : Vector3(fX, fY, fZ), _g_x(gX), _g_y(gY), _g_z(gZ) {

}

Vec3::Vec3(const lint agCoordinate[3], const Real afCoordinate[3]) : Vector3(afCoordinate), _g_x(agCoordinate[0]), _g_y(agCoordinate[1]), _g_z(agCoordinate[2]) {

}

Vec3::Vec3(const lint agCoordinate[3], const int afCoordinate[3]) : Vector3(afCoordinate), _g_x(agCoordinate[0]), _g_y(agCoordinate[1]), _g_z(agCoordinate[2]) {

}

Vec3::Vec3(lint * const g, Real * const r) : Vector3(r), _g_x(g[0]), _g_y(g[1]), _g_z(g[2]) {

}

Vec3::Vec3(const lint gscaler, const Real scaler) : Vector3(scaler), _g_x(gscaler), _g_y(gscaler), _g_z(gscaler) {

}

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
<<<<<<< HEAD
=======
    
>>>>>>> be121d877ecd90db4bbfda0ab7b37715053b98b0
    //
    return Ordinate(_x * val, _y * val, _z * val);
}
