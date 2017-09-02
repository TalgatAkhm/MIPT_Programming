#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <fstream>
#include <set>
#include <cmath>
#include <functional>
using namespace std;

bool solution_not_exist( vector<int> a, int zero_index )
{
	int count_inv = 0;

	for( int i = 0; i < 16; ++i )
		if( a[i] != 0 )
			for( int j = 0; j < i; ++j )
				if( a[j]>a[i] )
					++count_inv;

	count_inv += 1 + zero_index / 4;
	return ((count_inv & 1) ? true : false);
}

class board
{
public:
	board( ) :
		field( 16, 0 )
	{}
	board( vector<int> v, string w, int zero ) :
		field( v ),
		way( w ),
		zero_place( zero ){}

	bool check_win( )const;
	bool evristic_check_win( )const;
	int index_win( int condition_i )const;
	double dist_x( int p1, int p2 )const;
	double dist_y( int p1, int p2 )const;
	board move_zero_up( );
	board move_zero_down( );
	board move_zero_left( );
	board move_zero_right( );
	vector<pair<double, board>> move( );
	bool find_best_move( pair<double, board>& b1 );
	board& operator=(const board& another)
	{
		field = another.field;
		way = another.way;
		zero_place = another.zero_place;
		return *this;
	}
	double manhattan( )const;


	string get_way( )const{ return way; }
	int get_zero_place( )const { return zero_place; }
	vector<int> get_field( )const{ return field; }
private:
	int find_element_index( int element );
	string way;
	int zero_place;
	vector<int> field;
};


int board::find_element_index( int element )
{
	for( int i = 0; i < field.size( ); ++i )
		if( field[i] == element )
			return i;
	return -1;
}


bool operator < (const board& l, const board& r)
{
	if( l.manhattan( ) + l.get_way().length( ) < r.manhattan( ) + r.get_way().length( ) )
		return true;
	return false;
}


int board::index_win( int condition_i )const
{
	if( condition_i == 0 )
		return 15;
	return condition_i - 1;
}

bool board::check_win( )const
{
	for( int i = 0; i < 15; ++i )
		if( field[i] != i + 1 )
			return false;
	if( field[15] != 0 )
		return false;
	return true;
}

board board::move_zero_down( )
{
	board new_board( field, way, zero_place );

	if( zero_place + 4 <= 15 )
	{
		new_board.field[zero_place] = new_board.field[zero_place + 4];
		new_board.field[zero_place + 4] = 0;
		new_board.zero_place += 4;
		new_board.way += "U";
	}
	return new_board;
}

board board::move_zero_left( )
{
	board new_board( field, way, zero_place );
	if( zero_place != 0 && zero_place != 4 && zero_place != 8 && zero_place != 12 )
	{
		new_board.field[zero_place] = new_board.field[zero_place - 1];
		new_board.field[zero_place - 1] = 0;
		new_board.way += "R";
		--new_board.zero_place;
	}
	return new_board;
}

board board::move_zero_right( )
{
	board new_board( field, way, zero_place );

	if( zero_place != 3 && zero_place != 7 && zero_place != 11 && zero_place != 15 )
	{
		new_board.field[zero_place] = new_board.field[zero_place + 1];
		new_board.field[zero_place + 1] = 0;
		++new_board.zero_place;
		new_board.way += "L";
	}
	return new_board;
}

board board::move_zero_up( )
{
	board new_board( field, way, zero_place );
	if( zero_place - 4 >= 0 )
	{
		new_board.field[zero_place] = new_board.field[zero_place - 4];
		new_board.field[zero_place - 4] = 0;
		new_board.zero_place -= 4;
		new_board.way += "D";
	}
	return new_board;
}

double board::dist_x( int p1, int p2 )const
{
	return abs( p1 % 4 - index_win( p2 ) % 4 );
}

double board::dist_y( int p1, int p2 )const
{
	return abs( p1 / 4 - index_win( p2 ) / 4 );
}

double board::manhattan( )const
{
	double x = 0, y = 0;

	for( int i = 0; i < 16; ++i )
	{
		if( field[i] != 0 )
		{
			x += dist_x( i, field[i] );
			y += dist_y( i, field[i] );
		}
	}
	return static_cast<double>(max( x, y ));
}


string a_star( board cond )
{
	if( cond.manhattan( ) == 0 )
		return "";

	priority_queue<pair<double, board>> q;
	q.push( make_pair( -cond.manhattan( ), cond ));
	set<vector<int>> used;

	board tmp;
	board next_tmp;

	double manh = 0;
	const double hevr_const1 = 0.40;
	const double hevr_const2 = 1.0;
	const int q_max_len = 10000;

	while( !q.empty( ) )
	{
		if( q.size( ) > q_max_len )
		{
			const int c2 = 2700;
			vector<pair<double, board>> m;
			for( int i = 0; i < c2; ++i )
			{
				m.push_back( q.top( ) );
				q.pop( );
			}
			while( q.size( )>0 )
				q.pop( );
			for( int i = 0; i < c2; ++i )
				q.push( m[i] );
			m.clear( );
		}

		tmp = q.top( ).second;
		q.pop( );

		if( used.count( tmp.get_field() ) != 0 )
			continue;
		used.insert( tmp.get_field() );

		next_tmp = tmp.move_zero_down( );
		if( next_tmp.get_zero_place() != tmp.get_zero_place() )
		{
			manh = 0;
			if( (manh = next_tmp.manhattan( )) == 0  )
				return next_tmp.get_way();
			manh *= hevr_const2;
			manh += hevr_const1*next_tmp.get_way().length( );
			q.push( make_pair( -manh, next_tmp ) );
		}

		next_tmp = tmp.move_zero_up( );
		if( next_tmp.get_zero_place() != tmp.get_zero_place() )
		{
			manh = 0;
			if( (manh = next_tmp.manhattan( )) == 0  )
				return next_tmp.get_way();
			manh *= hevr_const2;
			manh += hevr_const1*next_tmp.get_way().length( );
			q.push( make_pair( -manh, next_tmp ) );
		}

		next_tmp = tmp.move_zero_left( );
		if( next_tmp.get_zero_place() != tmp.get_zero_place() )
		{
			manh = 0;
			if( (manh = next_tmp.manhattan( )) == 0  )
				return next_tmp.get_way();
			manh *= hevr_const2;
			manh += hevr_const1*next_tmp.get_way().length( );
			q.push( make_pair( -manh, next_tmp ) );
		}

		next_tmp = tmp.move_zero_right( );
		if( next_tmp.get_zero_place() != tmp.get_zero_place() )
		{
			manh = 0;
			if( (manh = next_tmp.manhattan( )) == 0 )
				return next_tmp.get_way();
			manh *= hevr_const2;
			manh += hevr_const1*next_tmp.get_way().length( );
			q.push( make_pair( -manh, next_tmp ) );
		}
		manh = 0;
	}
	return "";
}


int main( )
{
	vector<int> a( 16 );
	int zero = 0;
	for( int i = 0; i < 16; ++i )
	{
		cin >> a[i];
		if( a[i] == 0 )
			zero = i;
	}
	board b( a, "", zero );
	if( solution_not_exist( a, zero ) )
	{
		cout << -1;
		return 0;
	}
	string s = a_star( b );
	cout << s.length( ) << endl << s << endl;
	system( "pause" );
	return 0;
}