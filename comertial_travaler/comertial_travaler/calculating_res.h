#pragma once
#include <cmath>
#include <vector>
using namespace std;


class calculating_res
{
public:
	calculating_res( int num,double g, double r, vector<double> dev ) :
		g( g ), r( r ), deviations(dev), num(num){}
	void calc( );
private:
	double g;
	double r;
	int num;
	vector<double> deviations;
};