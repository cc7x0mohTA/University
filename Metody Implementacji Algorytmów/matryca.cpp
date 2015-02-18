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
	string s; cin >> s;

	bool takiesame = true;

	REP(i, SIZE(s)-1)
	{
		if(s[i] != s[i+1]) { takiesame = false; break; }
	}

	if(takiesame) printf("1\n");
	else
	{
		char znak = '*'; int pos = 0; int wynik = INF;

		REP(i, SIZE(s))
		{
			if(znak == '*' && s[i] != '*')
			{
				znak = s[i]; pos = i;
			}

			if(znak == s[i]) pos = i;

			if(znak != s[i] && s[i] != '*')
			{
				wynik = min(wynik, i-pos); pos = i; znak = s[i];
			}
		}

		if(wynik == INF) printf("1\n");
		else printf("%d\n", SIZE(s)-wynik+1);
	}

	return 0;
}