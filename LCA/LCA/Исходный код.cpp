#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <cmath>
using namespace std;

class list_dfs_tree
{
public:
	list_dfs_tree( ){}

	list_dfs_tree( long long n ) :
		num_verts( n ),
		timer( 0 ),
		list( n ),
		time_in( n ),
		time_out( n ),
		parrents( n, vector<long long>( log2( n ) + 1, 0 ) )
	{}

	void time_dfs( long long cur_vert, long long parrent = 0 );
	void add_edge( long long from, long long to );
	bool is_a_upper_b( long long a, long long b );
protected:
	vector<vector<long long>> list;
	vector<vector<long long>> parrents;
	vector<long long> time_in;
	vector<long long> time_out;

private:
	long long num_verts;
	long long timer;
};

void list_dfs_tree::add_edge( long long from, long long to )
{
	list[from].push_back( to );
	list[to].push_back( from );
}

void list_dfs_tree::time_dfs( long long cur_vert, long long parrent )
{
	time_in[cur_vert] = ++timer;
	parrents[cur_vert][0] = parrent;
	for( long long i = 1; i <= log2( num_verts ); ++i )
		parrents[cur_vert][i] = parrents[parrents[cur_vert][i - 1]][i - 1];
	for( long long i = 0; i < list[cur_vert].size( ); ++i )
	{
		long long to = list[cur_vert][i];
		if( to != parrent )
			time_dfs( to, cur_vert );
	}

	time_out[cur_vert] = ++timer;
}

bool list_dfs_tree::is_a_upper_b( long long a, long long b )
{
	return time_in[a] <= time_in[b] && time_out[a] >= time_out[b];
}


class lca_solver :public list_dfs_tree
{
public:
	lca_solver( ){};
	lca_solver( const vector<long long>& v, long long n, long long m, long long x, long long y, long long z, long long a1, long long a2 ) :
		list_dfs_tree( n ),
		num_vert( n ),
		num_req( m ),
		x( x ), y( y ), z( z ),
		a1( a1 ), a2( a2 )
	{
		for( long long i = 0; i < v.size( ); ++i )
			add_edge( v[i], i + 1 );
	}

	long long get_sum_of_parents( );
private:
	long long x;
	long long y;
	long long z;
	long long num_vert;
	long long num_req;
	long long a1;
	long long a2;

	long long generate_next_request( const long long& pre_cur_a, const long long& cur_a );
	long long lca( long long a, long long b );
};

long long lca_solver::generate_next_request( const long long& pre_cur_a, const long long& cur_a )
{
	return (x*pre_cur_a + y*cur_a + z) % num_vert;
}

long long lca_solver::lca( long long a, long long b )
{
	if( is_a_upper_b( a, b ) )
		return a;
	if( is_a_upper_b( b, a ) )
		return b;
	for( long long i = log2( num_vert ); i >= 0; --i )
		if( !is_a_upper_b( parrents[a][i], b ) )
			a = parrents[a][i];
	return parrents[a][0];
}

long long lca_solver::get_sum_of_parents( )
{
	time_dfs( 0 );
	long long sum = 0;
	long long result = 0;
	long long prev_a1 = a1;
	for( long long i = 0; i < num_req; ++i )
	{
		sum += (result = lca( a1, a2 ));
		prev_a1 = generate_next_request( prev_a1, a2 );
		a2 = generate_next_request( a2, prev_a1 );
		a1 = (prev_a1 + result) % num_vert;
	}
	return sum;
}

int main( )
{
	long long n, m;
	cin >> n >> m;
	vector<long long> v( n - 1 );
	for( long long i = 0; i < n - 1; ++i )
		scanf("%d", &v[i]);
	long long a1, a2;
	cin >> a1 >> a2;
	long long x, y, z;
	cin >> x >> y >> z;

	lca_solver solver( v, n, m, x, y, z, a1, a2 );
	cout << solver.get_sum_of_parents( );
	//system( "pause" );
	return 0;
}