#include <iostream>
#include "substring finder.h"
using namespace std;

int main( )
{
	string sub, m;
	cin >> sub >> m;

	substring_finder f( sub, m );
	vector<int> o(f.find_occurrences( ));
	for( auto i : o )
		cout << i << " ";


	return 0;
}