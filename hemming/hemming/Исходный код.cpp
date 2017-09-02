#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <limits.h>
#include <limits>
#include <queue>
using namespace std;



enum
{
	white,
	grey,
	black
};

///////////////////////////////////////////////////////////////////////

class matrix_graph
{
public:
	matrix_graph( int count_vertices );
	matrix_graph( );
	void add_edge( int from, int to, int flow );
	vector<vector<int>>& get_matrix( )
	{
		return matrix;
	}
	int vertices_count( ) const;
protected:
	int num_vertices;
	vector<vector<int>> matrix;
};

matrix_graph::matrix_graph( int count_vertices ) :
num_vertices( count_vertices ),
matrix( count_vertices, vector<int>( count_vertices, 0 ) ){}

matrix_graph::matrix_graph( ) :
num_vertices( 0 ),
matrix( 1 ){}

void matrix_graph::add_edge( int from, int to, int flow )
{
	matrix[from][to] += flow;
	matrix[to][from] += flow;
}

int matrix_graph::vertices_count( ) const
{
	return num_vertices;
}

///////////////////////////////////////////////////////////////////////

class cut_with_dinic :public matrix_graph
{
public:
	cut_with_dinic( int n ) :matrix_graph( n ),
		flows( n, vector<int>( n, 0 ) ),
		dist( n, INT_MAX ){}
	int max_flow( );
	vector<int> get_dists( ){ return dist; }
private:
	int dfs( int start, int f );
	bool bfs( );
	vector<vector<int>> flows;
	vector<int> dist;
	vector<int> p;
};

bool cut_with_dinic::bfs( )
{
	queue<int> q;
	q.push( 0 );
	dist.assign( num_vertices, INT_MAX );
	dist[0] = 0;
	int to;
	while( !q.empty( ) )
	{
		to = q.front( );
		q.pop( );
		for( int i = 0; i < num_vertices; ++i )
			if( flows[to][i] < matrix[to][i] && dist[i] == INT_MAX )
			{
				q.push( i );
				dist[i] = dist[to] + 1;
			}
	}
	if( dist[1] == INT_MAX )
		return false;
	return true;
}

int cut_with_dinic::dfs( int vert, int f )
{
	if( f == 0 || vert == 1 )
		return f;

	for( int i = p[vert]; i < num_vertices; ++i )
	{
		if( dist[i] == dist[vert] + 1/* && flows[vert][i] < matrix[vert][i]*/ )
		{
			int df = dfs( i, min( f, matrix[vert][i] - flows[vert][i] ) );
			if( df != 0 )
			{
				flows[vert][i] += df;
				flows[i][vert] -= df;
				return df;
			}
		}
		++p[vert];
	}
	return 0;
}

int cut_with_dinic::max_flow( )
{
	flows.assign( num_vertices, vector<int>( num_vertices, 0 ) );
	dist.assign( num_vertices, INT_MAX );
	int f = 0;
	while( bfs( ) )
	{
		p.assign( num_vertices, 0 );
		int df = dfs( 0, INT_MAX );
		while( df != 0 )
		{
			f += df;
			df = dfs( 0, INT_MAX );
		}
	}
	return f;
}

//////////////////////////////////////////////////////////////////////

class hamming_distance_and_co
{
public:
	static int get_hamming_distance( int start_pos, string str_to_calc, string pattern );
	static string ternary_string_builder( string str_with_questions );
	static int count_questions( const string& s, int start, int end = INT_MAX );
	static int get_str_index_of_current_question( string s, int number_of_question );
};

string hamming_distance_and_co::ternary_string_builder( string str_with_questions )
{
	string ternaty_str = "";
	for( auto c : str_with_questions )
		(c == '?') ? ternaty_str += '2' : ternaty_str += c;
	return ternaty_str;
}

int hamming_distance_and_co::get_hamming_distance( int start_pos, string str_to_calc, string pattern )
{
	int str_len = str_to_calc.length( );
	int dist = 0;
	for( int i = start_pos, j = 0; j < str_len; ++j, ++i )
		dist += abs( pattern[i] % 2 - str_to_calc[j] % 2 );
	return dist;
}

int hamming_distance_and_co::count_questions( const string& s, int start, int end )
{
	if( end == INT_MAX )
		end = s.length( ) + 1;
	int counter = 0;
	for( int i = start; i < end; ++i )
		if( s[i] == '2' || s[i] == '?' )
			++counter;
	return counter;
}

int hamming_distance_and_co::get_str_index_of_current_question( string s, int number_of_question )
{
	int index = -1;
	int len = s.length( );
	int count_question = 0;
	for( index = 0; index < len; ++index )
	{
		if( s[index] == '2' || s[index] == '?' )
			++count_question;

		if( count_question == number_of_question )
			return index;
	}
}

//////////////////////////////////////////////////////////////////////


class questions_configurator
{
public:
	questions_configurator( string smaller, string bigger ) :
		bigger( bigger ),
		smaller( smaller )
	{
		ternary_bigger = hamming_distance_and_co::ternary_string_builder( bigger );
		ternary_smaller = hamming_distance_and_co::ternary_string_builder( smaller );

	}

	questions_configurator( ) :
		bigger( "" ),
		smaller( "" ),
		ternary_bigger( "" ),
		ternary_smaller( "" ){};

	int fill_the_gaps( string& s1, string& s2 );

	void bfs_configurator( );
private:
	void init_graph(cut_with_dinic& g, int& c11, int& c22 );
	string bigger;
	string ternary_bigger;
	string smaller;
	string ternary_smaller;
	int num_elements;
};

void questions_configurator::init_graph(cut_with_dinic& g, int& c1, int& c2 )
{
	int count1, count2;

	for( int step = 0; step <= bigger.length( ) - smaller.length( ); ++step )
	{
		for( int i = 0; i < smaller.length( ); ++i )
		{
			if( smaller[i] == '?' && bigger[i + step] == '?' )
			{
				count1 = hamming_distance_and_co::count_questions( ternary_smaller, 0, i );
				count2 = hamming_distance_and_co::count_questions( ternary_bigger, 0, i + step );
				g.add_edge( count1 + 2, count2 + 2 + c1, 1 );
			}
			else if( smaller[i] == '?' )
			{
				int count1 = hamming_distance_and_co::count_questions( ternary_smaller, 0, i );
				int a = ternary_bigger[step + i] == '1' ? 1 : 0;
				g.add_edge( a, count1 + 2, 1 );
			}
			else if( bigger[i + step] == '?' )
			{
				int count2 = hamming_distance_and_co::count_questions( ternary_bigger, 0, step + i );
				int a = ternary_smaller[i] == '1' ? 1 : 0;
				g.add_edge( a, count2 + 2 + c1, 1 );
			}
			else if( smaller[i] != bigger[i + step] )
				g.add_edge( 0, 1, 1 );
		}
	}
}

int questions_configurator::fill_the_gaps( string& s1, string& s2 )
{
	int count1 = hamming_distance_and_co::count_questions( ternary_smaller, 0 );
	int count2 = hamming_distance_and_co::count_questions( ternary_bigger, 0 );
	int c1 = count1;
	int c2 = count2;
	int num_el = 2 + count1 + count2;

	num_elements = num_el;
	cut_with_dinic g( num_elements );
	init_graph( g, c1, c2 );

	int num_res = 0;
	num_res += g.max_flow( );

	int quest_counter = 2;
	vector<int> tmp_dist( g.get_dists( ) );
	s1 = smaller;
	s2 = bigger;
	for( int i = 0; i < smaller.length( ); ++i )
		if( s1[i] == '?' )
		{
			if( tmp_dist[quest_counter] == INT_MAX )
				s1[i] = '1';
			else
				s1[i] = '0';
			++quest_counter;
		}
	for( int i = 0; i < bigger.length( ); ++i )
		if( s2[i] == '?' )
		{
			if( tmp_dist[quest_counter] == INT_MAX )
				s2[i] = '1';
			else
				s2[i] = '0';
			++quest_counter;
		}
	return num_res;
}


///////////////////////////////////////////////////////////////

int main( )
{
	string s1, s2;
	cin >> s2 >> s1;
	questions_configurator conf( s1, s2 );
	cout<<conf.fill_the_gaps( s1, s2 )<<endl;
	cout << s2 << endl << s1 << endl;
	system( "pause" );
	return 0;
}