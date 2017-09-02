# pragma once
#include <vector>
using namespace std;

class matrix_graph
{
public:
	matrix_graph( int count_vertices );
	void add_edge( int from, int to, double weight );

	int vertices_count( ) const;

	void get_next_vertices( int vertex, vector<double>& vertices ) const;
	void get_prev_vertices( int vertex, vector<double>& vertices ) const;
	vector<vector<double>>& get_matrix( );
	matrix_graph& operator=(const matrix_graph& another);
protected:
	int num_vertices;
	vector<vector<double>> matrix;
};