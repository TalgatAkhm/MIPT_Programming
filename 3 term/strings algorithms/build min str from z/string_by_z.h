# pragma once
#include <string>
#include <vector>
using namespace std;

class string_builder
{
public:
	string_builder( );
	string_builder( const vector<int>& z );

	string build_str( );
private:
	string reconstruct;
	vector<int> prefixes;
	int current_letter_index;
	const string alphabet;
	const int ALPHABET_SIZE;
	vector<int> from_z_to_prefix(const vector<int>& z);
};