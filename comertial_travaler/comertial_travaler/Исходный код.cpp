#pragma once
#include <iostream>
#include <vector>
#include "generator1.h"
#include "commertial_traveler_solver.h"
#include "geometry.h"
#include "calculating_res.h"
using namespace std;



int main( )
{
	srand( time( NULL ) );
	int n = 7;
	vector<double> devs;
	double sum=0;
	double sum_g = 0;
	double sum_r = 0;
	for( int n = 3; n < 10; ++n )
	{
		cout << "points " << n << "tests "<< 9<< endl;
		for( int i = 0; i < 16; ++i )
		{
			vector<point> ps = generator::generate( n );
			commertial_traveler_solver solver( n, ps );
			double g = solver.get_approximate_solution( );
			double r = solver.get_exact_solution( );
			//cout << g / r << endl;
			devs.push_back( g - r );
			sum += g / r;
			sum_r += r;
			sum_g += g;
			cout << g / r << endl;
		}
		cout << sum / 16.0  << endl;
		sum = 0;

		calculating_res res( 5, 0, 0, devs );
		res.calc( );
		cout << " ------------------- " << endl;
	}
	system( "pause" );
	return 0;
}