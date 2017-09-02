#include "matrix_graph.h"

matrix_graph::matrix_graph( int count_vertices ) :
num_vertices( count_vertices ),
matrix(count_vertices, vector<double>(count_vertices,0 ))
{}

vector<vector<double>>& matrix_graph::get_matrix( )
{
	return matrix;
}

matrix_graph& matrix_graph::operator=(const matrix_graph& another)
{
	matrix = another.matrix;
	num_vertices = another.num_vertices;
	return *this;
}

void matrix_graph::add_edge( int from, int to, double weight )
{

	matrix[from][to] = weight;
	matrix[to][from] = weight;
}

int matrix_graph::vertices_count( ) const
{
	return num_vertices;
}

void matrix_graph::get_next_vertices( int vertex, vector<double>& vertices ) const
{
	vertices.clear( );
	for( int j = 0; j < num_vertices; ++j )
	{
		if( matrix[vertex][j] == 1 )
			vertices.push_back( j );
	}
}


void matrix_graph::get_prev_vertices( int vertex, vector<double>& vertices ) const
{
	vertices.clear( );
	for( int j = 0; j < num_vertices; ++j )
	{
		if( matrix[j][vertex] == 1 )
			vertices.push_back( j );
	}
}