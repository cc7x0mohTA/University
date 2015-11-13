#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdio>

#include <fstream>
#include <iostream>
#include <chrono> 

using namespace std;

struct case_insensitive // true if s1 < s2
{
	bool operator( ) ( const std::string& string1, const std::string& string2 ) const
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
	}
};

map<string, unsigned int, case_insensitive> frequencytable (const vector<string> &text)
{
	map<string, unsigned int, case_insensitive > mapa;
	for( auto iter = text.begin(); iter != text.end(); ++iter ) mapa[*iter]++;
	return mapa;
}

struct case_insensitive_hash
{
	size_t operator () ( const std::string& s) const
	{
		size_t w = 0;
		
		for(size_t i = 0; i < s.size(); i++)
		{
			w = (w * 29)%1000000007 + (tolower(s[i]) - 'a' + 1);
			w %= 1000000007;
		}

		return w;
	}
};

struct case_insensitive_equality
{
	bool operator( ) ( const std::string& string1, const std::string& string2 ) const
	{
		case_insensitive c;
		return !c(string1,string2) && !c(string2,string1);
	}
};

std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality > frequencytable_hash( const std::vector<std::string > & text )
{
	std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality > mapa;
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

std::ostream& operator << ( std::ostream& stream, const map< std::string, unsigned int, case_insensitive> &frq )
{
	for ( const auto &p : frq ) stream  << p.first << '\t' << p.second << "\n";
	return stream;
}

template< typename A, typename C >
std::pair < A, unsigned int > most_frequent ( const map<A, unsigned int, C > &mp )
{
	std::pair < A, unsigned int > most = * mp. begin( );

	for ( const auto &p : mp )
	{
		if(p.second > most.second) most = p;
	}

	return most;
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

	//auto most = most_frequent<string, case_insensitive> ( &M );

	//cout << "Most frequent : " << most.first << " " << most.second << "\n";

	return 0;
}
