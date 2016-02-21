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
typedef long double LD;
const double EPS = 10e-9;
const int INF = 1000000001;
const int MOD = 1000000007;

// Solution :

VI H;

struct Tree
{
	vector<LD> val; vector<LL> ans; int M, h;

	Tree(int _h)
	{
		M = H[_h]; h = _h;
		val.assign(2*M+5, 0);
		ans.assign(2*M+5, 0);
	}

	void Load()
	{
		FOR(i, 1, H[h]-1) cin >> ans[i];
		h--;
		FOR(i, H[h], H[h+1]-1) val[i] = ans[i];	// kopiowanie liści

	}
		/*
		Trzeba naprawić Query, bo jak się moduluje to
		może być tak że jakaś duża liczba przerobi sie na małą
		i wtedy się wszytko jebie.
		*/

	LL Query()
	{
		while(h--)
		{
			FOR(i, H[h], H[h+1]-1)
			{
            	int X = val[i<<1] > val[(i<<1)+1] ? i << 1 : (i<<1)+1;
				val[i] = ans[i] * val[X];
				ans[i] = ((LL) ans[i] * ans[X]) % MOD;    
            }
		}

		return (LL) ans[1];
	}

	void Delejt()
	{
		ans.clear(); val.clear();
	}
};


int main()
{
	std::ios_base::sync_with_stdio(false); cin.tie(0);
	H.resize(17); REP(i, 17) H[i] = 1 << i;

	int t;

	while(cin >> t)
	{
		if(t == 0) break;
		else
		{
			Tree Drzewko(t);
			Drzewko.Load();
			cout << Drzewko.Query() << "\n";
			Drzewko.Delejt();
		}
	}

	return 0;
}