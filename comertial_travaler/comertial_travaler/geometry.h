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


//struct edge
//{
//	int from;
//	int to;
//	double weight;
//	edge( ){}
//	edge( int f, int t, double w ) :from( f ), to( t ), weight( w ){ }
//
//	bool operator<(const edge& another)
//	{
//		if( weight < another.weight )
//			return true;
//		return false;
//	}
//	
//	edge& operator=(const edge& another)
//	{
//		from = another.from;
//		to = another.to;
//		weight = another.weight;
//		return *this;
//	}
//};
//
//bool operator<(const edge& e1, const edge& e2)
//{
//	return (e1.weight < e2.weight);
//}