/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

//#include "stdc++.h"
#include <bits/stdc++.h>
using namespace std;

#define FOR(x, b, e) for(int x = b; x <= (e); x++)
#define FORD(x, b, e) for(int x = b; x >= (e); x--)
#define REP(x, n) for(int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second

inline string IntToStr(int x) { ostringstream ss; ss << x; return ss.str(); }
inline int StrToInt(string x) { int i; istringstream iss(x); iss >> i; return i; }

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1000000000;

// Solution :

int main()
{
	std::ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;

	while(t--)
	{
		int n, k; cin >> n >> k;
		string s; cin >> s;
		
		map<int, string> mapa; mapa[0] = s;

		int t = 0;
		
		while(1)
		{
			t++;
			if(s[0] == '+') s[n-1] == '+' ? s[n-1] = '-' : s[n-1] = '+';
			string ss = s.substr(1,n-1); ss += s[0];
			s = ss;
			s[n-1] == '+' ? s[n-1] = '-' : s[n-1] = '+';
			mapa[t] = s;
			
			if(mapa[t] == mapa[0]) break;
		}

		while(k--)
		{
			int x; cin >> x; cout << mapa[x % t] << "\n";
		}
	}


	return 0;
}