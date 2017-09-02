#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <limits.h>
#include <limits>
using namespace std;

enum
{
	white,
	grey,
	black
};

class matrix_graph
{
public:
	matrix_graph( int count_vertices );
	matrix_graph( );
	void add_edge( int from, int to, int flow );

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
	//matrix[to][from] += flow;
}

int matrix_graph::vertices_count( ) const
{
	return num_vertices;
}

class max_flow_ford_fulkerson : public matrix_graph
{
public:
	max_flow_ford_fulkerson( int n ) :
		matrix_graph( n ){}
	int find_max_flow( int v_start, int v_finish );
private:
	bool bfs( vector<vector<int>>& flows, int start, int finish, vector<int>& parent );
};


bool max_flow_ford_fulkerson::bfs( vector<vector<int>>& flows, int start, int finish, vector<int>& parent )
{
	vector<int> color( num_vertices, white );
	int u, v;
	queue<int> q;
	q.push( start );
	parent[start] = -1;
	color[start] = grey;
	while( !q.empty( ) )
	{
		u = q.front( );
		q.pop( );
		color[u] = black;
		for( v = 0; v < num_vertices; ++v )
			if( color[v] == white && flows[u][v] > 0 )
			{
				q.push( v );
				color[v] = grey;
				parent[v] = u;
			}
	}

	if( color[finish] > 0 )
		return true;
	return false;
}

int max_flow_ford_fulkerson::find_max_flow( int v_start, int v_finish )
{
	int max_flow = 0;
	vector<vector<int>> flows( matrix );
	//flows = matrix;
	vector<int> parent( num_vertices );
	while( bfs( flows, v_start, v_finish, parent ) )
	{
		int u;
		int dflow = INT_MAX;
		for( int v = v_finish; v != v_start; v = parent[v] )
		{
			u = parent[v];
			dflow = min( dflow, flows[u][v] );
		}

		for( int v = v_finish; v != v_start; v = parent[v] )
		{
			u = parent[v];
			flows[u][v] -= dflow;
			flows[v][u] += dflow;
		}
		max_flow += dflow;
	}
	return max_flow;
}

int main( )
{
	ofstream out( "maxflow.out" );
	ifstream in( "maxflow.in" );

	int n = 0, m = 0;
	in >> n >> m;
	if( n == 0 )
		return 0;

	max_flow_ford_fulkerson a( n );
	int from, to, flow;
	for( int i = 0; i < m; ++i )
	{
		in >> from >> to >> flow;
		--from;
		--to;
		a.add_edge( from, to, flow );
	}
	out << a.find_max_flow( 0, n - 1 ) << endl;
	in.close( );
	out.close( );
	return 0;
}