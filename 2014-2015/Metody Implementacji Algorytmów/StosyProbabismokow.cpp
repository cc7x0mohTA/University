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

LL cost[3][3], MinCost[50][3][3];

LL Calc(int i, int j, int k)
{
	LL v1 = MinCost[i-1][j][3-j-k] + MinCost[i-1][3-j-k][k];
	v1 += cost[j][k];
	LL v2 = MinCost[i-1][j][k] + MinCost[i-1][k][j] + MinCost[i-1][j][k];
	v2 += cost[j][3-j-k] + cost[3-j-k][k];

	return min(v1,v2);
}

int main()
{

	REP(i, 3) REP(j, 3) scanf( "%lld", &(cost[i][j]) );
	int k, nic = 0; scanf("%d", &k);

	if(k == 0) { printf("0\n"); return 0; }

	FOR(K, 1, k) REP(i,3) REP(j,3) i != j ? MinCost[K][i][j] = Calc(K,i,j) : nic++;

	printf("%lld\n", MinCost[k][0][2]);

	return 0;
}