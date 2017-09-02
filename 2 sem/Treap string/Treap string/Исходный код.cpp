#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <algorithm>
#include <string>
#include <random>
using namespace std;

class treep
{
public:
	treep( ){}
	treep( int n ) :
		number( n ),
		root( nullptr ),
		last_priority( 0 ){}
	~treep( )
	{
		while( root != nullptr )
			delete_current_node( root, count( root->left ) + 1 );
	}

	bool insert_at( int position, string& val );
	bool delete_at( int position );
	string get_at( int position );
private:
	struct node
	{
		int priority;
		string value;
		int count;
		node* left;
		node* right;

		node( ) :priority( 0 ), count( 0 ),
			left( nullptr ),
			right( nullptr ),
			value( "NOT FILL VALUE" ){}

		node( string k, int p ) : priority( p ), value( k ), count( 1 ),
			left( nullptr ),
			right( nullptr ){}
	};

	int number;
	node* root;
	int last_priority;


	int count( node* current );
	void record_new_count( node* current );
	void push( node* current );
	void merge( node*& current, node* left_current, node* right_current );
	void split( node* current, node*& left_current, node*& right_current, int key, int addition = 0 );
	void reverse( node* current, int l, int r );

	bool delete_current_node( node*& current, int position );
	string find_current_position( node* current, int position );
};

int treep::count( node* current )
{
	return (current != nullptr ? current->count : 0);
}

void treep::record_new_count( node* current )
{
	if( current != nullptr )
		current->count = count( current->left ) + count( current->right ) + 1;
}

//void treep::push( node* current )
//{
//	if( current != nullptr && current->rev )
//	{
//		current->rev = false;
//		swap( current->left, current->right );
//		if( current->left != nullptr )
//			current->left->rev = true;
//		if( current->right != nullptr )
//			current->right->rev = true;
//	}
//}

void treep::merge( node*& current, node* left_current, node* right_current )
{
	//push( left_current );
	//push( right_current );

	if( left_current == nullptr || right_current == nullptr )
		current = (left_current != nullptr ? left_current : right_current);
	else if( left_current->priority > right_current->priority )
	{
		merge( left_current->right, left_current->right, right_current );
		current = left_current;
	}
	else
	{
		merge( right_current->left, left_current, right_current->left );
		current = right_current;
	}

	record_new_count( current );
}

void treep::split( node* current, node*& left_current, node*& right_current, int position, int addition )
{
	if( current == nullptr )
	{
		left_current = right_current = nullptr;
		return;
	}

	//push( current );
	int current_position = addition + count( current->left ) + 1;

	if( position <= current_position )
	{
		split( current->left, left_current, current->left, position, addition );
		right_current = current;
		record_new_count( current );
		return;
	}

	split( current->right, current->right, right_current, position, addition + current_position );
	left_current = current;
	record_new_count( current );
}

bool treep::insert_at( int position, string& val )
{
	position += 1;
	if( root == nullptr )
	{
		root = new node( val, ++last_priority );
		return true;
	}

	node* insert_node = new node( val, last_priority = (rand( )*(RAND_MAX - last_priority) + last_priority) );

	split( root, insert_node->left, insert_node->right, position );
	merge( root, insert_node->left, insert_node );
	merge( root, root, insert_node->right );
	//root = insert_node;

	return true;
}

bool treep::delete_at( int position )
{
	position += 1;
	return delete_current_node( root, position );
}

bool treep::delete_current_node( node*& current, int position )
{
	int current_position = count( current->left ) + 1;

	if( current_position == position )
	{
		merge( current, current->left, current->right );
		
	}
	else if( current_position > position )
		delete_current_node( current->left, position );
	else
		delete_current_node( current->right, position - current_position );

	record_new_count( current );
	return true;
}

string treep::get_at( int position )
{
	position += 1;
	return find_current_position( root, position );
}

string treep::find_current_position( node* current, int position )
{
	int current_position = count( current->left ) + 1;

	if( current_position == position )
		return current->value;
	else if( current_position > position )
		return find_current_position( current->left, position );
	else
		return find_current_position( current->right, position - current_position );
}

int main( )
{
	int num_req;
	cin >> num_req;

	char operation;
	string inp = "";
	int pos;

	treep tree( num_req );
	for( int i = 0; i < num_req; ++i )
	{
		cin >> operation >> pos;
		if( operation == '+' )
		{
			cin >> inp;
			tree.insert_at( pos, inp );
		}
		else if( operation == '-' )
			tree.delete_at( pos );
		else if( operation == '?' )
			cout << tree.get_at( pos ) << endl;
	}
	//system( "pause" );
	return 0;
}