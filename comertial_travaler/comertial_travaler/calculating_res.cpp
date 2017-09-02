#include<iostream>
#include "calculating_res.h"

void calculating_res::calc( )
{
	double sum = 0;
	for( auto d : deviations )
		sum += d;
	double med = sum / num;
	//std::cout << med<<std::endl;
	sum = 0;
	for( int i = 0; i < num; ++i )
		sum += pow( deviations[i] - med, 2 );
	sum += sqrt( sum / num );
	std::cout << sum * 100 << "%" << endl;
}