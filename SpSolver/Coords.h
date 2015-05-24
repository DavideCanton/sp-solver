#pragma once

#include <ostream>

class Coords
{
public:
	Coords();
	Coords(int, int);
	Coords(double, double);
	virtual ~Coords();
	
	int get_q() const
	{
		return q;
	}
	
	int get_r() const
	{
		return r;
	}

	friend std::ostream& operator<<(std::ostream& o, const Coords& coords)
	{
		o << "<" << coords.q << ", " << coords.r << ">";
		return o;
	}

	Coords operator+(const Coords& other) const;
	Coords& operator+=(const Coords& other);
	Coords operator*(const int a) const;

	bool operator==(const Coords& c) const
	{
		return q == c.q && r == c.r;
	}

	bool operator!=(const Coords& c) const
	{
		return !(*this == c);
	}

	size_t get_hash() const
	{
		return q * 17 + r * 13;
	}
	
private:
	int q;
	int r;
};


Coords operator*(const int, const Coords&);

namespace std
{
	template<>
	struct hash < Coords >
	{
		size_t operator()(const Coords& c) const
		{
			return c.get_hash();
		}
	};
}