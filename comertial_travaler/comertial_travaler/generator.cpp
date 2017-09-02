#pragma once
#include "generator1.h"
#include <cmath>

vector<point> generator::generate( int num )
{
	vector<point> points(num);
	double r, f;
	for( int i = 0; i < num; ++i )
	{
		r = double (rand( ))/RAND_MAX;
		f =  double(rand( ))/RAND_MAX;
		//r =1.0/ double( rand( ) );
		//f = 1.0 / double( rand( ) );
		points[i] = point( cos( 6.28 * f ) * sqrt( -2 * log( r ) ), sin( 6.28 * f ) * sqrt( -2 * log( r ) ) );
	}
	return points;
}
