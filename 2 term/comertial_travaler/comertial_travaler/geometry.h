#pragma once
#include <cmath>

struct  point
{
	point( double x, double y ) : x( x ), y( y ){};
	point( ){}
	bool operator<(const point& another)const
	{
		if( x < another.x )
			return true;
		else if( x > another.x )
			return false;
		return y < another.y;
	}
	double x;
	double y;
};

class geometry
{
public:
	static double get_dist( point p1, point p2 )
	{
		return sqrt( pow( (p1.x - p2.x), 2 ) + pow( (p1.y - p2.y), 2 ) );
	}
};

