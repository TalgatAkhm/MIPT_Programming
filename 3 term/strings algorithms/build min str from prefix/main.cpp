//https://contest.yandex.ru/contest/5005/run-report/4917008/
//task: Найти лексикографически-минимальную строку, построенную по префикс-функции, в алфавите a-z.

#pragma once
#include <iostream>
#include "string_builder_by_prefix.h"
#include <fstream>
using namespace std;

int main( )
{

	vector<int> p;
	int pref;
	ifstream in( "input.txt" );
	while( !in.eof() )
	{
		in >> pref;
		p.push_back( pref );
	}

	string_builder_by_prefix builder( p );
	cout << builder.build_str( );
	cout << endl;
	return 0;
}