#pragma once
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class substring_finder
{
public:
	substring_finder( );
	substring_finder(const string& substr,const string& mainstr );
	vector<int> find_occurrences( );
private:
	string substring;
	string mainstring;
	vector<int> substring_prefixes;
	vector<int> calculate_prefixes( );

	vector<int> kmp_algorithm( );
};