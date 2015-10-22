#include <iostream>
#include "stack.h"
using namespace std;

std::ostream& operator << ( std::ostream& stream, const stack& s )
{
	for( size_t i = 0; i < s. current_size; ++ i )
	   stream << " " << s. tab[i];
	return stream;
}

int main()
{
	stack s;

	//cout << "START\n";

	for( unsigned int i = 0; i < 10000000; ++ i )
	{
		//printf("%u\n", i);
		stack s1;
		s1. push(45); s1. push(45); s1. push(46);

		stack s2 = s1;
		// j is not size_t, because multiplying size_t with itself is
		// unnatural:
		for( unsigned int j = 0; j < 20; ++ j ) s2. push( j * j );

		s1 = s2;
		// Assignment.
		s1 = s1;
		// Self assignemnt should always be checked.

		// Won’t compile. In order to get it compiled, remove const:
		stack& sconst = s1;
		sconst. top( ) = 20;
		sconst. push(15);
	}

	cout << "END\n";

	stack s1;
	for(int i = 0; i < 10; i++) s1.push(i);
	cout << s1 << "\n";

	return 0;
}