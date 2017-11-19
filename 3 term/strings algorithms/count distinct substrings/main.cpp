#pragma once
#include "distinct_substr_finder.h"
#include <iostream>
#include <string>


int main()
{
	std::string txt;
	std::cin >> txt;
	distinct_substring_finder f( txt );
	std::cout<<f.count_distinct_substrings( )<<std::endl;
	return 0;
}