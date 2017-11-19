#pragma once
#include "pattern_finder.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>

using namespace std;



int main( )
{
	string text, pattern;
	//pattern = "ab??aba";
	//text = "ababacaba";
	cin >> pattern;
	cin >> text;
	pattern_finder f( pattern );
	vector<int> res( f.find_all_entries( text ) );
	for( auto i : res )
		cout << i << " ";
	return 0;
}