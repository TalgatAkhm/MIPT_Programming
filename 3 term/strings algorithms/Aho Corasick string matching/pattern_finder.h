#pragma once
#include "bohr_vertex.h"
#include "pattern_spliter.h"


class pattern_finder
{
public:
	pattern_finder( const string& p ) :
		pattern_text( p ),
		counter( m.length( ), 0 )
	{
		//pattern_spliter spliter;
		auto spled = pattern_spliter::split_for_special_symbols( pattern_text );
		bohr.push_back( make_bohr_vertex( 0, '#' ) ); //init bohr

		for( int i = 0; i < spled.first.size( ); ++i )
			add_string_to_bohr( spled.second[i], spled.first[i] );

		num_patterns = spled.first.size( );
	}

	vector<int> find_all_entries( );


private:
	//const int ENG_ALPH = 26;
	int num_patterns;

	vector<bohr_vertex> bohr;

	vector<int> counter;
	string pattern_text;


	bohr_vertex make_bohr_vertex( int p, char c );
	void add_string_to_bohr( const string& s, int position );
	bool is_string_in_bohr( const string& s );
	int get_auto_move( int vertex, char ch );
	int get_suff_link( int vertex );
	int get_suff_flink( int vertex );
	void check( int vertex, int i );

};