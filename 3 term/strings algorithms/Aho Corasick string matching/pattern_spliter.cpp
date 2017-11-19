#include "pattern_spliter.h"


pair<vector<int>, vector<string>> pattern_spliter::split_for_special_symbols( const string& text )
{
	pair<vector<int>, vector<string>> res;

	string collect = "";
	int index = 0;
	for( int i = 0; i < text.length( ); ++i )
	{
		if( text[i] != '?' && collect == "" )
		{
			collect += text[i];
			index = i;
		}
		else if( text[i] != '?' )
			collect += text[i];
		else if( collect.length( ) > 0 )
		{
			res.first.push_back( (index) );
			res.second.push_back( collect );
			collect = "";
		}
	}

	if( collect.length( ) > 0 )
	{
		res.first.push_back( (index) );
		res.second.push_back( collect );
		collect = "";
	}
	//num_patterns = res.first.size( );
	//num_patterns = res.first.size( );
	return (res);
}