# pragma once
#include <string>
#include <vector>
using namespace std;

class string_builder_by_prefix
{
public:
	string_builder_by_prefix( );
	string_builder_by_prefix( const vector<int>& p );
	string build_str( );
private:
	string reconstruct;
	vector<int> prefixes;
	int current_letter_index;
	const string alphabet;
	const int ALPHABET_SIZE;
};