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
const int MAXN = 652;

// Solution:

int n, dp[MAXN][MAXN], pom[MAXN][MAXN];
vector<pii> Pary;

inline int Suma(int a, int b, int c, int d)
{
	if(c < 0 || d < 0) return 0;
	return dp[c][d] + (a > 0 ? -dp[a-1][d] : 0) + (b > 0 ? -dp[c][b-1] : 0) + ((a > 0 && b > 0) ? dp[a-1][b-1] : 0);
}

inline void Prepare()
{
	scanf("%d", &n); Pary.resize(n);

	REP(i, n)
	{
		int x, y; scanf("%d %d", &x, &y);
		pom[x][y]++; Pary[i] = pii(make_pair(x,y));
	}

	FOR(i, 0, 650) FOR(j, 0, 650)
	{
		dp[i][j] = pom[i][j];
		dp[i][j] += (i > 0 ? dp[i - 1][j] : 0) + ( j > 0 ? dp[i][j - 1] : 0 ) - ( (i > 0 && j > 0) ? dp[i - 1][j - 1] : 0 );
	}
}

inline pii Query(int i)
{
	int x = Pary[i].ST, y = Pary[i].ND;
	int najw = 1 + Suma(x+1, y+1, 650, 650);
	int najm = n - Suma(0, 0, x-1, y-1);

	if(x == 650) najm -= pom[0][y];
	if(y == 650) najm -= pom[x][0];

	return pii(make_pair(najw, najm));
}

void Solve()
{
	REP(i, n)
	{
		pii w = Query(i); printf("%d %d\n", w.ST, w.ND);
	}
}

int main()
{
	Prepare();
	Solve();

	return 0;
}