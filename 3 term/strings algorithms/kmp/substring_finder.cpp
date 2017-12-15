#pragma once
#include "substring finder.h"

substring_finder::substring_finder( ) :
substring( "" ),
mainstring( "" ){}

substring_finder::substring_finder( const string& sub, const string& main ) :
substring( sub ),
mainstring( main ),
substring_prefixes( calculate_prefixes( ) )
{}

//abcdabcabcdabcdab
vector<int> substring_finder::calculate_prefixes( )
{
	vector<int> prefixes( substring.length( ) );
	for( int k = 0, i = 1; i < substring.length( ); ++i )
	{
		while( k>0 && substring[i] != substring[k] )
			k = prefixes[k - 1];

		if( substring[i] == substring[k] )
			++k;

		prefixes[i] = k;
	}
	return prefixes;
}

vector<int> substring_finder::find_occurrences( )
{
	return kmp_algorithm( );
}


vector<int> substring_finder::kmp_algorithm( )
{
	vector<int> occurrences_indexes;
	int index = -1;
	int k = 0;
	int mlen = mainstring.length( );

	for( int i = 0; i < mlen; ++i )
	{

		while( k>0 && mainstring[i] != substring[k] )
			k = substring_prefixes[k - 1];

		if( mainstring[i] == substring[k] )
			++k;

		if( k == substring.length() )
		{
			index = i - substring.length() + 1;
			occurrences_indexes.push_back( index );
		}
	}


	return occurrences_indexes;
}
