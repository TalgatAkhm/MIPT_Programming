#pragma once
#include <cmath>
#include <algorithm>


#include "commertial_traveler_solver.h"

long long fact( int x )
{
	long long r = 1;
	for( int i = 1; i <= x; ++i )
		r *= i;
	return r;
}

void commertial_traveler_solver::prim( vector<int>& order )
{
	set<pair<double, int>> q;
	vector<bool> used( num_points, false );
	used[0] = true;
	order.push_back( 0 );
	for( int i = 0; i < num_points; ++i )
		q.insert( make_pair( matrix[0][i], i ) );

	pair<double,int> current_edge( 0, 0 );
	pair<double, int> tmp;

	for( int i = 1; i < num_points + 1; )
	{
		if( q.empty( ) )
			break;
		current_edge = *(q.begin( ));
		q.erase( current_edge );
		if( !used[current_edge.second] )
		{
			used[current_edge.second] = true;
			order.push_back(current_edge.second );
			++i;
			for( int j = 0; j < num_points && matrix[current_edge.second][j] != INT_MAX; ++j )
				q.insert( make_pair( matrix[current_edge.second][j], j ) );
		}
	}
}

double commertial_traveler_solver::get_approximate_solution( )
{
	double sum_dist = 0;
	vector<int> order;
	prim( order );
	sum_dist += matrix[order[num_points - 1]][order[0]];
	for( int i = 1; i < num_points; ++i )
		sum_dist += matrix[order[i - 1]][order[i]];
	return sum_dist;
}

double commertial_traveler_solver::get_exact_solution( )
{
	vector<int> points_order;
	for( int i = 0; i < num_points; ++i )
		points_order.push_back( i );

	double min_way_len = INT_MAX;
	double cur_min_way_len = 0;
	long long permutations = fact( num_points );
	vector<point> temp_order( points );

	for( int i = 0; i < permutations; ++i )
	{
		cur_min_way_len = 0;
		for( int j = 1; j < temp_order.size( ); ++j )
			cur_min_way_len += geometry::get_dist( temp_order[j - 1], temp_order[j] );
		cur_min_way_len += geometry::get_dist( temp_order[0], temp_order[num_points - 1] );

		min_way_len = min( min_way_len, cur_min_way_len );
		next_permutation( temp_order.begin( ), temp_order.end( ) );
	}
	return min_way_len;
}
