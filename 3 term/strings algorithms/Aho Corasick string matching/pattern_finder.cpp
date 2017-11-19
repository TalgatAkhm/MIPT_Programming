#pragma once
#include "pattern_finder.h"


bohr_vertex pattern_finder::make_bohr_vertex( int p, char c )
{
	bohr_vertex vertex;
	//(255)=(2^8-1)=(все единицы в каждом байте памяти)=(-1 в дополнительном коде целого 4-байтного числа int)
	memset( vertex.next_vertex, 255, sizeof( vertex.next_vertex ) );
	vertex.flag = false;
	vertex.suff_link = -1;
	memset( vertex.auto_move, 255, sizeof( vertex.auto_move ) );
	vertex.parrent = p;
	vertex.symb = c;
	vertex.suff_flink = -1;

	return vertex;
}



void pattern_finder::add_string_to_bohr( const string& s, int position )
{
	int num = 0;
	for( int i = 0; i < s.length( ); i++ )
	{
		char ch = s[i] - 'a';
		if( bohr[num].next_vertex[ch] == -1 )
		{
			bohr.push_back( make_bohr_vertex( num, ch ) );
			bohr[num].next_vertex[ch] = bohr.size( ) - 1;
		}
		num = bohr[num].next_vertex[ch];
	}
	bohr[num].flag = true;
	bohr[num].pattern_info.position.push_back( position );
	bohr[num].pattern_info.length_of_subpattern.push_back( s.size( ) );
}



bool pattern_finder::is_string_in_bohr( const string& s )
{
	int num = 0;
	for( int i = 0; i < s.length( ); i++ ){
		char ch = s[i] - 'a';
		if( bohr[num].next_vertex[ch] == -1 )
		{
			return false;
		}
		num = bohr[num].next_vertex[ch];
	}
	return true;
}


int pattern_finder::get_auto_move( int vertex, char ch )
{
	if( bohr[vertex].auto_move[ch] == -1 )
		if( bohr[vertex].next_vertex[ch] != -1 )
			bohr[vertex].auto_move[ch] = bohr[vertex].next_vertex[ch];
		else
			if( vertex == 0 )
				bohr[vertex].auto_move[ch] = 0;
			else
				bohr[vertex].auto_move[ch] = get_auto_move( get_suff_link( vertex ), ch );
	return bohr[vertex].auto_move[ch];
}


int pattern_finder::get_suff_link( int vertex )
{
	if( bohr[vertex].suff_link == -1 ) //если еще не считали
		if( vertex == 0 || bohr[vertex].parrent == 0 ) //если vertex - корень или предок vertex - корень
			bohr[vertex].suff_link = 0;
		else
			bohr[vertex].suff_link = get_auto_move( get_suff_link( bohr[vertex].parrent ), bohr[vertex].symb );
	return bohr[vertex].suff_link;
}

int pattern_finder::get_suff_flink( int vertex )
{
	if( bohr[vertex].suff_flink == -1 )
	{
		int current_vertex = get_suff_link( vertex );
		if( current_vertex == 0 ) //либо vertex - корень, либо суф. ссылка vertex указывает на корень 
			bohr[vertex].suff_flink = 0;
		else
			bohr[vertex].suff_flink = (bohr[current_vertex].flag) ? current_vertex : get_suff_flink( current_vertex );
	}
	return bohr[vertex].suff_flink;
}





//move by good suffix links(suff_flink) on the bohr
void pattern_finder::check( int vertex, int i )
{
	for( int current_vertex = vertex; current_vertex != 0; current_vertex = get_suff_flink( current_vertex ) )
	{
		if( bohr[current_vertex].flag )
		{
			int p = i - bohr[current_vertex].pattern_info.length_of_subpattern[0] + 1;

			for( int j = 0; j < bohr[current_vertex].pattern_info.position.size( ) /*num_patterns*/; ++j )
			{
				int tmp_position = bohr[current_vertex].pattern_info.position[j]
				if( (p >= tmp_position)
					++counter[p - tmp_position];
			}
		}
	}
}

vector<int> pattern_finder::find_all_entries(const string& main_text )
{
	vector<int> res;
	int current_vertex = 0;
	for( int i = 0; i < main_text.length( ); ++i )
	{
		current_vertex = get_auto_move( current_vertex, main_text[i] - 'a' );
		check( current_vertex, i );
	}
	if( pattern_text.size( )>0 )
	{
		const int TXTSIZE = main_text.size( );
		const int PTTRN_SIZE = pattern_text.size( );
		const int DELTA_SIZE = TXTSIZE - PTTRN_SIZE + 1;
		for( int i = 0; i < DELTA_SIZE; ++i )
		{
			if( counter[i] == num_patterns )
				//cout << i << " ";
				res.push_back( i );
		}
	}
	return res;
}

