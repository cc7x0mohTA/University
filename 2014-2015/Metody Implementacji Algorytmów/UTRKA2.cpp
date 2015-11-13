#include <iostream>
#include <set>
using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false); 
	int n; cin >> n;
	std::multiset<string> Set;
	std::multiset<string>::iterator it;

	for(int i = 0; i < n; i++)
	{
		string s; cin >> s;
		Set.insert(s);
	}

	for(int i = 0; i < n-1; i++)
	{
		string s; cin >> s; it = Set.find(s); Set.erase(it);
	}

	it = Set.begin();

	cout << *it << "\n";

	return 0;
}