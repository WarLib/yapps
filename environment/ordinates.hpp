#ifndef _ORDINATES_HPP
#define _ORDINATES_HPP

enum ord {	X,Y,Z };

class Ordinate {
protected:
	double _x;
	double _y;
	double _z;
public:
	Ordinate();
	Ordinate(double x, double y, double z);
	double GetOrdinates(ord index);
	double Value(void) const;
	double Distance(const Ordinate& vgl) const;

	bool operator<(const Ordinate& vgl) const;
	Ordinate operator-(const Ordinate& vgl) const;
        void operator*=(double val);
        Ordinate operator*(double val) const;
};

#endif
