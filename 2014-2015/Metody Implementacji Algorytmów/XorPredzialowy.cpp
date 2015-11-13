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

// Solution :

int main()
{
	int t; scanf("%d", &t);

	while(t--)
	{
		int a, b; scanf("%d %d", &a, &b);

		if(b - a + 1 < 10)
		{
			int wynik = 0;
			FOR(i,a,b) wynik ^= i;
			printf("%d\n", wynik);
		}
		else
		{
			int wynik = 0;

			while(a % 4 != 0)
			{
				wynik ^= a; a++;
			}

			while(b % 4 != 3)
			{
				wynik ^= b; b--;
			}

			printf("%d\n", wynik);
		}
	}

	return 0;
}