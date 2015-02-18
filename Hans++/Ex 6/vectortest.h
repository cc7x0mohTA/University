
#ifndef VECTORTEST_INCLUDED
#define VECTORTEST_INCLUDED  1

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace vectortest
{
	void sort1( std::vector< std::string > & v );
	void sort2( std::vector< std::string > & v );
	void sort3( std::vector< std::string > & v );
	void sort4( std::vector< std::string > & v );

}

std::ostream& operator << ( std::ostream& , const std::vector< std::string > & );

#endif