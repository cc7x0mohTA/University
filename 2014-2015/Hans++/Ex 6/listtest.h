#ifndef LISTTEST_INCLUDED
#define LISTTEST_INCLUDED   1

#include <list> 
#include <vector> 
#include <string> 
#include <fstream>
#include <iostream>
#include <algorithm>

// I agree that the use of namespace in this little exercise
// is a bit exagerate, but one has to learn this technique.

namespace listtest 
{
   void sort1( std::list< std::string > & v );
   void sort2( std::list< std::string > & v );
}

std::ostream& operator << ( std::ostream& , const std::list< std::string > & ); 

#endif