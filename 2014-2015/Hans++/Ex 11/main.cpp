
#include "varchain.h"
#include "polynomial.h"
#include "bigint.h"
#include "rational.h"


template< typename N > polynomial< N > exptaylor( unsigned int n )
{
   varchain v;

   N fact = 1;

   polynomial< N > result;
   for( unsigned int i = 0; i < n; ++ i )
   {
      result[v] += fact;
      v = v * powvar( "x" );
      fact = fact / (i+1);
   }

   return result;
}

int main( int argc, char* argv [] )
{
   std::cout << "hello\n";
   
   varchain test1("x",2);
   varchain test2("x");
   varchain test3({powvar("x",2), powvar("x",3), powvar("x",7), powvar("x"), powvar("x",2), powvar("y",2), powvar("z",0)});
   varchain test4({powvar("a",0), powvar("x",2), powvar("x",3), powvar("x",0), powvar("y",3), powvar("y",-2), powvar("y",-1), powvar("z",0)});
   
   std::cout << test1 << " " << test2 << std::endl;
   std::cout << test3 << std::endl;
   std::cout << test4 << std::endl;
   std::cout << test4 * test3 << std::endl;
   
/*   polynomial< rational > polTest;

   polTest[ { } ] = 1;
   polTest[ { "x" } ] = rational( 1, 50 );
   polTest[ { "y" } ] = rational( 1, 2 );
   
   std::cout << "PolTest = " << polTest << "\n";
   std::cout << "PolTest^2 = " << polTest * polTest << "\n";
*/

//---------------------------------------------------------

   polynomial< rational > pol;

   int N = 50;

   pol[ { } ] = 1;
   pol[ { "x" } ] = rational( 1, N ); 

   
   polynomial< rational > res = 1;
 
   for( int i = 0; i < N; ++ i )
      res = res * pol;

   std::cout << "result = " << res << "\n";

   std::cout << " taylor expansion = " << exptaylor<rational>(20) << "\n";

   std::cout << "difference = " ;  
   std::cout << res - exptaylor<rational> ( 40 ) << "\n";
 
   return 0;
}


