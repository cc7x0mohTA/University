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

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1000000999;
const int MAXN = 400;

int dp[MAXN+5][MAXN+5], V[MAXN+5], n;

int main()
{
	while(scanf("%d", &n))
	{
		if(n == 0) return 0;

		FOR(i, 1, 2*n) FOR(j, 1, 2*n) dp[i][j] = 0;

		FOR(i, 1, n) scanf("%d", &V[i]);

		FOR(k, 3, n)
		{
			FOR(i, 1, n)
			{
				FOR(j, i+1, i+k-2)
				{
					dp[i][i+k-1] = max(dp[i][i+k-1], dp[i][j] + dp[j][i+k-1] + V[i] + V[i+k-1] + V[j]);
				}
			}
		}

		printf("%d\n", dp[1][n]);
	}
}