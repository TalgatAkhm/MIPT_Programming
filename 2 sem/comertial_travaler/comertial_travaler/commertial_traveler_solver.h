#pragma once
#include "matrix_graph.h"
#include "geometry.h"
#include <set>

class commertial_traveler_solver: public matrix_graph
{
public:
	commertial_traveler_solver( int num, vector<point> ps ) :matrix_graph( num ), points( ps ), num_points( num )/*, min_gr(num )*/
	{
		for( int i = 0; i < num; ++i )
			for( int j = 0; j < num; ++j )
				matrix[i][j] = geometry::get_dist( ps[i], ps[j] );
	}
	double get_approximate_solution( );
	double get_exact_solution( );
private:
	vector<point> points;
	int num_points;

//	matrix_graph get_min_spanning_tree_graph( );
//	matrix_graph min_gr;
	double count_approximate_solution( );

	//double dfs_
	void prim( vector<int>& order );
};