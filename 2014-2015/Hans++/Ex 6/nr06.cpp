
#include <fstream>
#include <iostream>
#include <chrono> 

#include "listtest.h"
#include "vectortest.h"

void readfile( std::istream& input, std::vector< std::string > & vect ) 
{
   if( !input.good() ) return;  // It was a short pleasure. 
   
   std::string lastword = "";

   while( input.good() )
   {
      int c = input.get();

      if(isspace(c) || ispunct(c) || !isprint(c))
      {
         if(lastword.size() > 0) vect.push_back(lastword), lastword = "";
      }
      else lastword += (char) c;
   }

   if(lastword.size() > 0) vect.push_back(lastword);

   //std::cout << "vect size : " << vect.size() << "\n";
}

// Anonymous namespace. This means that this function
// is guaranteed to be unique in the program, so that
// we don't have to worry about makelowercase functions defined
// in other files.

namespace
{
   // 'inline' is ignored by the compiler, but it makes me feel better.

   inline void makelowercase( std::string& s )
   {
      for( char& c : s ) c = tolower(c);
   }
}

void makelowercase( std::vector< std::string > & vect )
{
   for( auto& s : vect ) makelowercase(s);
}

std::list< std::string > makelist( const std::vector< std::string > & vect )
{
   std::list< std::string> result;
   for( const auto& s : vect ) result. push_back(s);
   return result;
}

void testvec(std::vector< std::string > vect, int i)
{
   auto t1 = std::chrono::high_resolution_clock::now( ); 
   
   if(i == 1) vectortest::sort1( vect );
   else if(i == 2) vectortest::sort2( vect );
   else if(i == 3) vectortest::sort3( vect );
   else vectortest::sort4( vect );
   
   
   auto t2 = std::chrono::high_resolution_clock::now( );

   std::chrono::duration< double > d = ( t2 - t1 );
   
   //std::cout << vect << "\n";

   std::cout << "sorting took " << d.count( ) << " seconds\n";
}

void testlist(std::list< std::string > lst, int i)
{
   auto t1 = std::chrono::high_resolution_clock::now( ); 
   
   i == 1 ? listtest::sort1( lst ) : listtest::sort2( lst );
   
   auto t2 = std::chrono::high_resolution_clock::now( );

   std::chrono::duration< double > d = ( t2 - t1 );
   
   //std::cout << lst << "\n";

   std::cout << "sorting took " << d.count( ) << " seconds\n";
}


int main( int argc, char* argv [] )
{

   std::vector< std::string > vect;

   // This use of int is one of those ugly remainders of C--.

   for( int i = 1; i != argc; ++ i )
   {
      std::ifstream input{ argv[i] }; 
      if( !input )
      {
         std::cerr << "could not open input file " << argv[i] << "\n";
      }
      else
      {
         readfile( input, vect ); 
      }
   }

   makelowercase( vect );

   //std::cout << "Vector :\n" << vect << "\n";
   std::list< std::string > lst = makelist( vect );
   //std::cout << "List :\n" << lst << "\n";


   std::cout << "Vector sorting :\n";

   for(int i = 1; i <= 4; i++) testvec(vect, i);

   std::cout << "List sorting :\n";

   for(int i = 1; i <= 2; i++) testlist(lst, i);
   
   return 0;
}