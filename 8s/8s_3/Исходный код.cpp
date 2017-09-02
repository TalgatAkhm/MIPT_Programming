#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_set>
#include <fstream>
using namespace std;


int get_current_digit( int number, int place )
{
	if( place == 8 )
		return number % 10;
	number /= pow( 10, 8 - place );
	return number % 10;
}

bool solve_not_exist( vector<int>& desc, int zero_index )
{
	int count = 0;
	for( int i = 0; i < 9; ++i )
		for( int j = i; j < 9; ++j )
			if( desc[i]>desc[j] )
				++count;
	count += zero_index;
	if( count % 2 != 0 )
		return true;
	return false;
}

class board
{
public:
	board( ){}
	board( int b, string w ) :
		field( b ),
		way( w ){}

	board( const board& another ) :
		field( another.field ),
		way( another.way ),
		zero_place( another.zero_place ){}

	bool check_win( )const;
	board move_up( );
	board move_down( );
	board move_left( );
	board move_right( );
	string get_way( );
	board& operator=(const board& another);
	int set_current_digit( int pos, int dig );

	int zero_place;
	int field;
private:
	string way;

};

string board::get_way( )
{
	return way;
}

board& board::operator=(const board& another)
{
	field = another.field;
	way = another.way;
	zero_place = another.zero_place;
	return *this;
}

int board::set_current_digit( int pos, int dig )
{
	int spliter = 0;
	int num = 0;
	int old_field = field;
	int n = 1;
	for( int i = 0; i < 9; ++i )
	{
		//old_field %= 10;
		spliter = get_current_digit( field, i );
		if( i == pos )
			spliter = dig;
		num += pow( 10, 8 - i ) * spliter;

		old_field /= 10;
	}
	field = num;
	return num;
}



bool board::check_win( )const
{
	if( field == 123456789 )
		return true;
	return false;
}
board board::move_down( )
{
	board new_board(*this);
	//new_board = *this;
	if( zero_place + 3 > 8)
		return new_board;
	new_board.set_current_digit( zero_place + 3, 9 );
	new_board.set_current_digit( zero_place, get_current_digit( field, zero_place + 3 ) );
	new_board.zero_place += 3;
	new_board.way += "D";
	return new_board;
}

board board::move_left( )
{
	board new_board(*this);
	//new_board = *this;
	if( zero_place - 1 < 0 || zero_place == 3 || zero_place == 6 )
		return new_board;
	new_board.set_current_digit( zero_place - 1, 9 );
	new_board.set_current_digit( zero_place, get_current_digit( field, zero_place - 1 ) );
	new_board.zero_place -= 1;
	new_board.way += "L";
	return new_board;
}

board board::move_right( )
{
	board new_board(*this);
	//new_board = *this;
	if( zero_place == 8 || zero_place == 2 || zero_place == 5 )
		return new_board;
	new_board.set_current_digit( zero_place + 1, 9 );
	new_board.set_current_digit( zero_place, get_current_digit( field, zero_place + 1 ) );
	new_board.zero_place += 1;
	new_board.way += "R";
	return new_board;
}

board board::move_up( )
{
	board new_board(*this);
	//new_board = *this;
	if( zero_place - 3 < 0 )
		return new_board;
	new_board.set_current_digit( zero_place - 3, 9 );
	new_board.set_current_digit( zero_place, get_current_digit( field, zero_place - 3 ) );
	new_board.zero_place -= 3;
	new_board.way += "U";
	return new_board;

}


string bfs( board cond )
{
	//362880
	queue<board> q;
	q.push( cond );
	unordered_set<int> used(362881);
	used.insert( cond.field );
	board tmp;
	board next_tmp;
	while( !q.empty( ) )
	{
		tmp = q.front( );
		q.pop( );
		
		next_tmp = tmp.move_down( );
	
		if( used.count( next_tmp.field ) == 0 )
		{
			used.insert( next_tmp.field );
			if( next_tmp.check_win( ) )
				return next_tmp.get_way();
			q.push( next_tmp );
		}
		
		next_tmp = tmp.move_up( );
		
		
	if( used.count( next_tmp.field ) == 0 )
		{
			if( next_tmp.check_win( ) )
				return next_tmp.get_way( );
			used.insert( next_tmp.field );
			q.push( next_tmp );
	}
		
		next_tmp = tmp.move_left( );
		
		if( used.count( next_tmp.field ) == 0 )
		{
			used.insert( next_tmp.field );
			if( next_tmp.check_win( ) )
				return next_tmp.get_way( );
			q.push( next_tmp );
		}
		
		next_tmp = tmp.move_right( );
		
		if( used.count( next_tmp.field ) == 0 )
		{
			used.insert( next_tmp.field );
			if( next_tmp.check_win( ) )
				return next_tmp.get_way( );
			q.push( next_tmp );
		}
	}
	return "";
}


int main( )
{
	int dig;
	int num = 0;
	int zero;
	ofstream out( "puzzle.out" );
	ifstream in( "puzzle.in" );
	vector<int> inp_d;
	for( int i = 0; i < 9; ++i )
	{
		in >> dig;
		if( dig == 0 || dig == 9 )
		{
			dig = 9;
			zero = i;
		}
		num = num * 10 + dig;
		inp_d.push_back( dig );
	}
	if( solve_not_exist( inp_d, zero ) )
	{
		out << "-1" << endl;
		return 0;
	}

	board b( num, "" );
	b.zero_place = zero;
	string s = bfs( b );

	out << s.length( ) << endl << s << endl;
	out.close( );
	in.close( );
	return 0;
}