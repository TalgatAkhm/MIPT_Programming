//https://contest.yandex.ru/contest/5005/run-report/4939047/
//Найти лексикографически-минимальную строку, построенную по z-функции, в алфавите a-z.

#pragma once
#include <iostream>
#include "string_by_z.h"
#include <fstream>
using namespace std;

int main( )
{

	vector<int> z;
	int z_element;
	ifstream in( "input.txt" );
	while( in >> z_element )
	{
		z.push_back( z_element );
	}

	string_builder builder( z );
	cout << builder.build_str( );
	return 0;
}