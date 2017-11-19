#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits.h>
using namespace std;

class rmq_solver
{
public:

	rmq_solver( vector<int>& a, int array_size ) :
		inp_array( a ),
		number_el( array_size ),
		sparse_table( array_size )
	{
		fill_ST( );
	}

	int get_res_of_requests( pair<int, int>& segment );
private:
	vector<int> inp_array;
	vector<vector<pair<int, int>>> sparse_table;
	vector<vector<int>> indexes;
	void fill_ST( );
	int number_el;
	pair<int, int> get_two_min_pair( pair<int, int>& p1, pair<int, int>& p2 );
};

pair<int, int> rmq_solver::get_two_min_pair( pair<int, int>& p1, pair<int, int>& p2 )
{
	vector<int> sorting_v;
	sorting_v.push_back( p1.first );
	sorting_v.push_back( p1.second );
	sorting_v.push_back( p2.first );
	sorting_v.push_back( p2.second );
	sort( sorting_v.begin( ), sorting_v.end( ) );
	return make_pair( sorting_v[0], sorting_v[1] );
}


int rmq_solver::get_res_of_requests( pair<int, int>& segment )
{
	vector<int> mins;
	int k = static_cast<int>(log2( segment.second - segment.first + 1 ));
	int t = segment.second - (pow( 2, k )) + 1;

	if( sparse_table[k][segment.first].first == sparse_table[k][t].first )
		return min( sparse_table[k][segment.first].second, sparse_table[k][t].second );

	mins.push_back( sparse_table[k][segment.first].first );
	mins.push_back( sparse_table[k][t].first );
	mins.push_back( sparse_table[k][segment.first].second );
	mins.push_back( sparse_table[k][t].second );
	sort( mins.begin( ), mins.end( ) );

	return mins[1];
}

void rmq_solver::fill_ST( )
{
	for( int i = 0; i < number_el; ++i )
	{
		pair<int, int> tmp( inp_array[i], inp_array[i] );
		sparse_table[0].push_back( tmp );
	}
	for( int i = 0; i + 1 < number_el; ++i )
	{
		pair<int, int> tmp( min( inp_array[i], inp_array[i + 1] ), max( inp_array[i], inp_array[i + 1] ) );
		sparse_table[1].push_back( tmp );
	}


	for( int k = 2; pow( 2, k ) < number_el; ++k )
		for( int i = 0; i + pow( 2, k - 1 ) < sparse_table[k - 1].size( ); ++i )
		{
			pair<int, int> min_seg1 = sparse_table[k - 1][i];
			pair<int, int> min_seg2 = sparse_table[k - 1][i + pow( 2, k - 1 )];
			sparse_table[k].push_back( get_two_min_pair( min_seg1, min_seg2 ) );
		}
}


int main( )
{
	int n, m;
	cin >> n >> m;

	vector<int> a( n, 0 );
	for( int i = 0; i < n; ++i )
		scanf( "%d", &a[i] );

	vector<pair<int, int>> segments( m, make_pair( 0, 0 ) );
	pair<int, int> seg( 0, 0 );
	for( int i = 0; i < m; ++i )
	{
		scanf( "%d %d", &seg.first, &seg.second );
		--seg.first;
		--seg.second;
		segments[i] = seg;
	}

	rmq_solver solver( a, n );
	for( int i = 0; i < m; ++i )
		printf( "%d %s", solver.get_res_of_requests( segments[i] ), "\n" );
	return 0;
}