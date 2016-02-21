#include "tree.h"

int main( int argc, char* argv [ ] )
{
	for(int i = 0; i < 100000; i++)
	{
		tree t1( std::string( "a" ));
		tree t2( std::string( "b" )); 
		tree t3 = tree( std::string( "f" ), { t1, t2 } ); 
		
		std::vector< tree > arguments = { t1, t2, t3 };

		std::cout << t3;

		std::cout << tree( "F", std::move( arguments )) << "\n";

		t2 = t3;
		t2 = std::move(t3);
	}

	return 0;
}