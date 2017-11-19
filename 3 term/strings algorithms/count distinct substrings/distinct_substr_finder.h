#pragma once
#include <vector>
#include <string>

class distinct_substring_finder
{
public:
	distinct_substring_finder( const std::string& txt ) :
		text( txt ),
		suff_arr_size(txt.length()),
		lcp(txt.length(), 0),
		suff_arr(txt.length()),
		inverse_suff_arr( txt.length(),0 )
	{}
	int count_distinct_substrings( );

private:
	std::string text;
	std::vector<int> suff_arr;
	std::vector<int> lcp;
	std::vector<int> inverse_suff_arr;
	int suff_arr_size;
	const int ALPHLEN = 256;
	const char ENDSTR = '$';


	struct suffixnode
	{
		int index;
		int rang[2];
		bool operator<(const suffixnode& other);
	};


	void kasai_longest_common_prefix( );
	void class_initer_suffarr_builder( );
	void pre_init_letter_counter( std::vector<int>& special_letter_counter );
};