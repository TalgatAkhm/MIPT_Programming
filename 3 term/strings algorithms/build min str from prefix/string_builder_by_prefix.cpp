#include "string_builder_by_prefix.h"

string_builder_by_prefix::string_builder_by_prefix( ) :
prefixes( 0 ),
reconstruct( "" ),
alphabet( "abcdefghijklmnopqrstuvwxyz" ),
current_letter_index( 0 ),
ALPHABET_SIZE( 26 ){}

string_builder_by_prefix::string_builder_by_prefix( const vector<int>& p ) :
prefixes( p ),
reconstruct( "" ),
alphabet( "abcdefghijklmnopqrstuvwxyz" ),
ALPHABET_SIZE( 26 ),
current_letter_index( 0 ){}


///returns minimal string by prefix array
string string_builder_by_prefix::build_str( )
{
	int psize = prefixes.size( );
	

	for( int i = 0; i < psize; ++i )
		if( prefixes[i] == 0 )
		{
			vector<bool> allowed( ALPHABET_SIZE, true );
			for( int j = i - 1; j >= 0; j = prefixes[j] - 1 )
				allowed[reconstruct[prefixes[j]] - alphabet[0]] = false;

			for( int j = 0; j < ALPHABET_SIZE; ++j )
				if( allowed[j] )
				{
					reconstruct += alphabet[j];
					break;
				}
			allowed.resize( ALPHABET_SIZE, true );
		}
		else
			reconstruct += reconstruct[prefixes[i] - 1];


	return reconstruct;
}