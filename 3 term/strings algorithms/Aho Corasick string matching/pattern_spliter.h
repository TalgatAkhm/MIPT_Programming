#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::pair;


class pattern_spliter
{
public:
	//gives the splited string & their indexes in base string
	static pair<vector<int>, vector<string>> split_for_special_symbols( const string& s );
};
