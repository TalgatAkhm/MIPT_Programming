#include "string_by_z.h"

string_builder::string_builder( ) :
prefixes( 0 ),
reconstruct( "" ),
alphabet( "abcdefghijklmnopqrstuvwxyz" ),
current_letter_index( 0 ),
ALPHABET_SIZE( 26 ){}

string_builder::string_builder( const vector<int>& z ) :
prefixes( from_z_to_prefix(z) ),
reconstruct( "" ),
alphabet( "abcdefghijklmnopqrstuvwxyz" ),
ALPHABET_SIZE( 26 ),
current_letter_index( 0 ){}


///returns string by z function array using prefix problem solution
string string_builder::build_str( )
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


///returns array of prefixes by z function array
vector<int> string_builder::from_z_to_prefix(const vector<int>& z )
{
	vector<int> p( z.size( ), 0);
	for( int i = 1; i < z.size( ); ++i )
		if( z[i] != 0 )
			for( int j = z[i] - 1; j >= 0 && (p[i + j]==0); --j )
				p[i + j] = j + 1;
	return p;
}