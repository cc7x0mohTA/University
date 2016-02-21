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
const int MAXN = 1000005;

// Solution :

int n, m, dx, dy, x, y, gen[MAXN], ans[MAXN];

void Generuj()
{
	int a = x, b = y;

	REP(i, n)
	{
		a += dx; a %= n;
		b += dy; b %= n;
		gen[a] = b;
	}
}

void WczytajRozyczki()
{
	REP(i, m) { scanf("%d %d", &x, &y); ans[(y-gen[x]+n)%n]++; }
}

int Odp()
{
	int odp = 0;
	REP(i, n+1) odp = max(odp, ans[i]);
	return odp;
}

int main()
{
	scanf("%d %d %d %d", &n, &m, &dx, &dy);

	Generuj();
	WczytajRozyczki();
	printf("%d\n", Odp());

	return 0;
}