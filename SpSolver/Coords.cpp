#include "Coords.h"

Coords::Coords() : q(0), r(0)
{
}

Coords::Coords(int q, int r) : q(q), r(r)
{
}

Coords::Coords(double qd, double rd)
{
	double x = qd;
	double z = rd;
	double y = -x - z;

	int rx = static_cast<int>(round(x));
	int ry = static_cast<int>(round(y));
	int rz = static_cast<int>(round(z));

	double x_diff = abs(rx - x);
	double y_diff = abs(ry - y);
	double z_diff = abs(rz - z);

	if (x_diff > y_diff && x_diff > z_diff)
		rx = -ry - rz;
	else if (y_diff > z_diff)
		ry = -rx - rz;
	else
		rz = -rx - ry;

	this->q = static_cast<int>(rx);
	this->r = static_cast<int>(rz);
}

Coords::~Coords()
{
}


Coords Coords::operator+(const Coords& other) const
{
	Coords c;
	c.q = q + other.q;
	c.r = r + other.r;
	return c;
}

Coords& Coords::operator+=(const Coords& other)
{
	q += other.q;
	r += other.r;
	return *this;
}


Coords Coords::operator*(const int a) const
{
	Coords c(q * a, r * a);	
	return c;
}

Coords operator*(const int a, const Coords& c)
{
	return c * a;
}