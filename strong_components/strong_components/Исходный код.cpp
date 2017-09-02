#include <vector>
#include <iostream>

using namespace std;

class strong_rel_graph
{
public:
	strong_rel_graph( int count_vertices );

	void AddEdge( int from, int to );
	int VerticesCount( ) const
	{
		return num_vertices;
	}

	int count_edges_to_add( ); 

private:
	int num_vertices;
	vector<vector<int> > in; //входящие ребра
	vector<vector<int> > out; //исходящие ребра

	vector<int> color; //colors of verts
	vector<int> order; //order of search in dfs1
	vector<int> strong_comp; //components of graph
	int current_color; //current color to differ verts


	vector<bool> btw_strongs_in; //verts come in strong component
	vector<bool> btw_strongs_out; //verts come out strong component

	void dfs1( int vertex );  //first dfs to know the order
	void dfs2( int vertex ); //second dfs to color verts
};

strong_rel_graph::strong_rel_graph( int count_vertices ) :
num_vertices( count_vertices ),
in( count_vertices ),
out( count_vertices ),
current_color(0 )
{
	color.assign( count_vertices + 5, 0 );
	btw_strongs_in.assign( count_vertices + 1, false );
	btw_strongs_out.assign( count_vertices+1, false );
}




void strong_rel_graph::dfs1( int vertex )
{
	color[vertex] = 1;
	for( int i = 0; i < out[vertex].size( ); ++i )
		if( color[ out[vertex][i] ] == 0 ) //if we havent visited this vert
			dfs1( out[vertex][i] );
	order.push_back( vertex ); //back order
}

void strong_rel_graph::dfs2( int vertex )
{
	color[vertex] = current_color;
	strong_comp.push_back( vertex );
	for( int i = 0; i < in[vertex].size( ); ++i )
	{
		if( color[in[vertex][i]] == 0 )
			dfs2( in[vertex][i] );
	}
	
}


int strong_rel_graph::count_edges_to_add( )
{
	
	for( int i = 0; i < num_vertices; ++i )
		if( color[i] == 0 )
			dfs1( i );
	color.clear( ); //clear binaryy colored from dfs1 array, to recolor verts in dfs2
	color.assign( num_vertices, 0 );
	
	for( int i = 0; i < num_vertices; ++i ) //back order
	{ 
		int vert = order[num_vertices-1-i];
		if( color[vert] ==0 )
		{
			++current_color; 
			dfs2( vert );
			
		
		}
	}
	
	
	if( current_color == 1 ) //if we have bunary colored graph, we dont have to add any edge
		return 0;

	for( int i = 0; i < out.size(); ++i ) //count how many edges come to the strong comp
		for( int j = 0; j < out[i].size(); ++j )
		{
			if( color[i] != color[out[i][j]] )
			{
				btw_strongs_out[color[i]] = true;
				btw_strongs_in[color[out[i][j]]] = true;
			}
		}

	
	int count_zero_in=0;
	int count_zero_out=0;
	for( int i = 1; i < current_color+1; ++i )
	{
		if( btw_strongs_in[i] == false )
			++count_zero_in;
		if( btw_strongs_out[i] == false )
			++count_zero_out;
	}

	return count_zero_in>count_zero_out ? count_zero_in : count_zero_out ;
}


void strong_rel_graph::AddEdge( int from, int to )
{	
	in[to].push_back( from );
	out[from].push_back( to );

}

int main( )
{
	int v,e;
	cin >> v;
	//cout << "1 ";
	strong_rel_graph g( v );
	cin >> e;
	if( e == 0 )
	{
		cout << v;
		return 0;
	}

	int f, t;
	for( int i = 0; i < e; ++i )
	{
		cin >> f >> t;
		--f;
		--t;
		g.AddEdge( f, t );
	}
	cout/*<<"result "*/ << g.count_edges_to_add( ) << endl;
	return 0;
}