#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <fstream>
using namespace std;


class list_graph
{
public:
	list_graph( int count_vertices );
	void add_edge( int from, int to, int dist );
	int vertices_count( ) const
	{
		return num_vertices;
	}

	void get_next_vertices( int vertex, vector<pair<int, int>>& vertices ) const;
private:
	int num_vertices;
	vector<vector<pair<int, int>>> graph;
};

list_graph::list_graph( int count_vertices ) :
num_vertices( count_vertices ),
graph( count_vertices * 2 ) {}


void list_graph::get_next_vertices( int vertex, vector<pair<int, int>>& vertices )const
{
	vertices = graph[vertex];
}

void list_graph::add_edge( int from, int to, int dist )
{
	graph[from].push_back( make_pair( to, dist ) );
	graph[to].push_back( make_pair( from, dist ) );
}

int prima( const list_graph& g )
{
	set<pair<int, int>> q;
	vector<bool> used( g.vertices_count( ), false );
	int min_tree_len = 0;

	vector<pair<int, int>> next;
	q.insert( make_pair( 0, 0 ) );
	pair<int, int> current_edge( 0, 0 );
	pair<int, int> tmp;
	for( int i = 0; i < g.vertices_count( ) + 1; )
	{
		if( q.size( ) == 0 )
			break;

		current_edge = *q.begin( );
		q.erase( current_edge );

		if( !used[current_edge.second] )
		{
			min_tree_len += current_edge.first;
			used[current_edge.second] = true;
			g.get_next_vertices( current_edge.second, next );
			++i;
			for( int j = 0; j < next.size( ); ++j )
				q.insert( make_pair( next[j].second, next[j].first ) );
		}
	}
	return min_tree_len;
}

int main( )
{
	int n, m;
	ifstream in( "kruskal.in" );
	ofstream out( "kruskal.out" );
	in >> n >> m;
	double w;
	list_graph g( n );
	int from, to;
	for( int i = 0; i < m; ++i )
	{
		in >> from >> to >> w;
		g.add_edge( from - 1, to - 1, w );
	}
	out << prima( g );
	in.close( );
	out.close( );
	return 0;
}
