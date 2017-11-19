#pragma once
#include "distinct_substr_finder.h"
#include <algorithm>
using namespace std;

bool distinct_substring_finder::suffixnode::operator<(const suffixnode& other)
{
	if( rang[0] == other.rang[0] )
	{
		if( rang[1] < rang[1] )
			return true;
		return false;
	}
	else if( rang[0] < other.rang[0] )
		return true;
	return false;
}


void distinct_substring_finder::pre_init_letter_counter( vector<int>& special_letter_counter )
{
	for( int i = 0; i < suff_arr_size; ++i )
		++special_letter_counter[text[i]];
	for( int i = 1; i < ALPHLEN; ++i )
		special_letter_counter[i] += special_letter_counter[i - 1];
	for( int i = 0; i < suff_arr_size; ++i )
		suff_arr[--special_letter_counter[text[i]]] = i;
}


void distinct_substring_finder::class_initer_suffarr_builder( )
{
	text += ENDSTR;
	vector <int> special_letter_counter( ALPHLEN );
	pre_init_letter_counter( special_letter_counter );
		
	inverse_suff_arr[suff_arr[0]] = 0;
	int classes = 1;
	for( int i = 1; i < suff_arr_size; ++i )
	{
		if( text[suff_arr[i]] != text[suff_arr[i - 1]] )
			++classes;
		inverse_suff_arr[suff_arr[i]] = classes - 1;
	}


	vector<int> tmp_suff_arr( suff_arr_size );
	vector<int> tmp_inverse_suff_arr( suff_arr_size );

	for( int k = 0; (1 << k) < suff_arr_size; ++k )
	{
		for( int i = 0; i < suff_arr_size; ++i )
		{
			tmp_suff_arr[i] = suff_arr[i] - (1 << k);
			if( tmp_suff_arr[i] < 0 )  
				tmp_suff_arr[i] += suff_arr_size;
		}

		for( int i = 0; i < classes; ++i )
			special_letter_counter[i] = 0;

		for( int i = 0; i < suff_arr_size; ++i )
			++special_letter_counter[inverse_suff_arr[tmp_suff_arr[i]]];
		for( int i = 1; i < classes; ++i )
			special_letter_counter[i] += special_letter_counter[i - 1];
		for( int i = suff_arr_size - 1; i >= 0; --i )
			suff_arr[--special_letter_counter[inverse_suff_arr[tmp_suff_arr[i]]]] = tmp_suff_arr[i];

		tmp_inverse_suff_arr[suff_arr[0]] = 0;
		classes = 1;
		for( int i = 1; i < suff_arr_size; ++i )
		{
			int mid1 = (suff_arr[i] + (1 << k)) % suff_arr_size, mid2 = (suff_arr[i - 1] + (1 << k)) % suff_arr_size;
			if( inverse_suff_arr[suff_arr[i]] != inverse_suff_arr[suff_arr[i - 1]] || inverse_suff_arr[mid1] != inverse_suff_arr[mid2] )
				++classes;
			tmp_inverse_suff_arr[suff_arr[i]] = classes - 1;

			for( int i = 0; i < suff_arr_size; ++i )
				inverse_suff_arr[i] = tmp_inverse_suff_arr[i];
		}
	}

	for( int i = 0; i < suff_arr_size; ++i )
			inverse_suff_arr[suff_arr[i]] = i;
}

void distinct_substring_finder::kasai_longest_common_prefix( )
{
	int k = 0;

	for( int i = 0; i < suff_arr_size; i++ )
	{
		if( k > 0 )
			--k;
		if( inverse_suff_arr[i] == suff_arr_size - 1 )
		{
			lcp[suff_arr_size - 1] == -1;
			k = 0;
		}
		else
		{
			int j = suff_arr[inverse_suff_arr[i] + 1];

			while( i + k < suff_arr_size && j + k < suff_arr_size && text[i + k] == text[j + k] )
				k++;

			lcp[inverse_suff_arr[i]] = k;
		}
	}
}


int distinct_substring_finder::count_distinct_substrings( )
{
	class_initer_suffarr_builder( );
	kasai_longest_common_prefix( );
	int res = suff_arr_size - suff_arr[0];

	for( int i = 1; i < suff_arr_size; ++i )
		res += (suff_arr_size - suff_arr[i] - lcp[i - 1]);

	return res;
}