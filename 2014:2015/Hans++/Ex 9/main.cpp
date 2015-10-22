#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <chrono> 
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

auto case_insensitve = [] (const std::string& string1, const std::string& string2)
{
	auto p2 = string2.begin();

	for(auto p1 = string1.begin(); p1 != string1.end(); ++p1)
	{
		if(p2 == string2.end()) return false;
		if(tolower(*p1) < tolower(*p2)) return true;
		if(tolower(*p1) > tolower(*p2)) return false;
		p2++;
	}

	if(p2 != string2.end()) return true;
	return false;
};


auto case_insensitive_hash = [] ( const std::string& s )
{
	size_t w = 0;
	
	for(size_t i = 0; i < s.size(); i++)
	{
		w = (w * 29)%1000000007 + (tolower(s[i]) - 'a' + 1);
		w %= 1000000007;
	}

	return w;
};

auto case_insensitive_equality = [] ( const std::string& string1, const std::string& string2 )
{
	return !case_insensitve(string1,string2) && !case_insensitve(string2,string1);
};


map<string, unsigned int, decltype(case_insensitve)> frequencytable (const vector<string> &text)
{
	map<string, unsigned int, decltype(case_insensitve) > mapa{case_insensitve};
	for( auto iter = text.begin(); iter != text.end(); ++iter ) mapa[*iter]++;
	return mapa;
}

unordered_map<string, unsigned int, decltype(case_insensitive_hash), decltype(case_insensitive_equality) > frequencytable_hash( const std::vector<std::string > & text )
{
	unordered_map<string, unsigned int, decltype(case_insensitive_hash), decltype(case_insensitive_equality)> mapa{10, case_insensitive_hash, case_insensitive_equality};
	for( auto iter = text.begin(); iter != text.end(); ++iter ) mapa[*iter]++;
	return mapa;
}

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

template< typename C >
std::ostream& operator << ( std::ostream& stream, const map< std::string, unsigned int, C > &frq )
{
	for ( const auto &p : frq ) stream  << p.first << '\t' << p.second << "\n";
	return stream;
}

int main( int argc, char* argv [] )
{

	vector< std::string > vect;

	for( int i = 1; i != argc; ++ i )
	{
		std::ifstream input{ argv[i] }; 
		if( !input ) std::cerr << "could not open input file " << argv[i] << "\n";
		else readfile( input, vect );
	}

	auto t1 = std::chrono::high_resolution_clock::now( );
	auto M = frequencytable_hash( vect ); 
	auto t2 = std::chrono::high_resolution_clock::now( );
	std::chrono::duration< double > d = ( t2 - t1 );
	std::cout << "Unordered_Map : " << d.count( ) << " seconds\n";

	auto t3 = std::chrono::high_resolution_clock::now( );
	auto MM = frequencytable( vect ); 
	auto t4 = std::chrono::high_resolution_clock::now( );
	std::chrono::duration< double > dd = ( t4 - t3 );
	std::cout << "Map : " << dd.count( ) << " seconds\n";

	cout << MM << "\n";

	return 0;
}