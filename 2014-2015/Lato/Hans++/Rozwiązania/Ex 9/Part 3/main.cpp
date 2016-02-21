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

bool case_insensitve(const std::string& string1, const std::string& string2)
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


size_t case_insensitive_hash( const std::string& s )
{
	size_t w = 0;
	
	for(size_t i = 0; i < s.size(); i++)
	{
		w = (w * 29)%1000000007 + (tolower(s[i]) - 'a' + 1);
		w %= 1000000007;
	}

	return w;
};

bool case_insensitive_equality( const std::string& string1, const std::string& string2 )
{
	return !case_insensitve(string1,string2) && !case_insensitve(string2,string1);
};


map<std::string, unsigned int, bool(*)(const std::string&,const std::string&)>
frequencytable(const std::vector<std::string>& text, bool (*comp)(const std::string&,const std::string&))
{
	map<string, unsigned int, bool(*)(const std::string&,const std::string&)> mapa{comp};
	for( auto iter = text.begin(); iter != text.end(); ++iter ) mapa[*iter]++;
	return mapa;
}

template< typename H, typename E >
std::unordered_map<std::string,unsigned int, H*, E* >
pointer_hashed_frequencytable(const std::vector<std::string>& text, const H* hsh, const E* eq )
{
	std::unordered_map<std::string,unsigned int,H*, E* > tmp{0,hsh,eq};
	for(const std::string& s: text) tmp[s]++;
	return tmp;
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
	auto M = pointer_hashed_frequencytable( vect, &case_insensitive_hash, &case_insensitive_equality ); 
	auto t2 = std::chrono::high_resolution_clock::now( );
	std::chrono::duration< double > d = ( t2 - t1 );
	std::cout << "Unordered_Map : " << d.count( ) << " seconds\n";

	auto t3 = std::chrono::high_resolution_clock::now( );
	auto MM = frequencytable( vect, case_insensitve ); 
	auto t4 = std::chrono::high_resolution_clock::now( );
	std::chrono::duration< double > dd = ( t4 - t3 );
	std::cout << "Map : " << dd.count( ) << " seconds\n";

	cout << MM << "\n";
	return 0;
}
