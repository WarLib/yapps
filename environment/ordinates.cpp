#include "ordinates.hpp"
#include <cmath>

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
    return Ordinate(_x * val, _y * val, _z * val);
}
