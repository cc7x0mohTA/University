#include "listtest.h"

std::ostream& operator << ( std::ostream& stream, const std::list< std::string > & L)
{
	for(auto &i : L) stream << i << "\n";
	return stream;
}

// 1st version : (iterator + swap)

void listtest::sort1( std::list< std::string > & v )
{
	for( auto q = v. begin( ); q != v. end( ); ++ q )
	{
		for( auto p = v. begin( ); p != q; ++ p )
		{
			if( *p > *q ) std::swap( *p, *q );
		}
	}
}

// 2nd version : (iterator + assignments)

void listtest::sort2( std::list< std::string > & v )
{
	for( auto q = v. begin( ); q != v. end( ); ++ q )
	{
		for( auto p = v. begin( ); p != q; ++ p )
		{
			if( *p > *q )
			{
				std::string s = *p;
				*p = *q;
				*q = s;
			}
		}
	}
}