#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

// 3)

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

// 1)

map<string, unsigned int, case_insensitive> frequencytable (const vector<string> &text)
{
	map<string, unsigned int, case_insensitive > mapa;
	for( auto iter = text.begin(); iter != text.end(); ++iter ) mapa[*iter]++;
	return mapa;
}

// 2)

std::ostream& operator << ( std::ostream& stream, const map< std::string, unsigned int, case_insensitive> &frq )
{
	for ( const auto &p : frq ) stream  << p.first << '\t' << p.second << "\n";
	return stream;
}

// 4)

void Ex4()
{
	cout << frequencytable(vector<string> {"AA", "aA", "Aa", "this", "THIS"});
	case_insensitive c;
	cout << c("a", "A") << " " << c("a", "b") << " " << c("A", "b") << "\n";
}

// 5)

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

void Ex5()
{
	case_insensitive_hash h;
	cout << h("xxz") << " " << h("XXX") << "\n";
	cout << h("Abc") << " " << h("abC") << "\n";
	case_insensitive_equality e;
	std::cout << e("xxx", "XXX") << "\n";
}

// 6)

using maptype = std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality > ;

maptype frequencytable_hash( const std::vector<std::string > & text )
{
	std::unordered_map<std::string, unsigned int, case_insensitive_hash, case_insensitive_equality > mapa;
	for( auto iter = text.begin(); iter != text.end(); ++iter ) mapa[*iter]++;
	return mapa;
}

int main()
{
	//Ex4();
	//Ex5();
	auto M = frequencytable_hash(vector<string> {"Aa","aa", "bb", "Cab"} );
	cout << M["aa"] << "\n";

	return 0;
}
