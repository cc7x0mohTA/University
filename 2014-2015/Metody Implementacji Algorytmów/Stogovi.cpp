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
const int MAXN = 300000;
const int MAXLOG = 20;

int nrstosu[MAXN+5], p[MAXN+5][MAXLOG+5], h[MAXN+5];

int LCA(int u, int v)
{
	if(h[u] < h[v]) swap(u,v);
	int H = h[u] - h[v];

	for(int i = 0; ; i++)
	{
		if(H % 2 == 1) u = p[u][i];
		H >>= 1;

		if(H == 0) break;
	}

	if(u == v) return u;

	FORD(i, MAXLOG-1, 0)
	{
		if(p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
	}

	return p[u][0];
}

void QueryA(int i)
{
	int x, pom; cin >> x; x = nrstosu[x];
	p[i][0] = x; nrstosu[i] = i; h[i] = h[x]; h[i]++; pom = x;
	FOR(j, 1, MAXLOG-1) (h[i] < (1 << j)) ? p[i][j] = 0 : pom = p[pom][j - 1], p[i][j] = pom;
}

void QueryB(int i)
{
	int x; cin >> x; x = nrstosu[x];
	cout << x << "\n"; nrstosu[i] = p[x][0];
}

void QueryC(int i)
{
	int x, y; cin >> x >> y;
	x = nrstosu[x]; y = nrstosu[y];
	cout << h[LCA(x,y)] << "\n"; nrstosu[i] = x;
}

int main()
{
	std::ios_base::sync_with_stdio(false); cin.tie(0);

	int t; cin >> t;

	FOR(i, 1, t)
	{
		char c; cin >> c;
		if(c == 'a') QueryA(i);
		else if(c == 'b') QueryB(i);
		else QueryC(i);
	}

	return 0;
}