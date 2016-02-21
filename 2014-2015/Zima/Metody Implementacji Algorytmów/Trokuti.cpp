/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

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
const int INF = 1000000001;

// Solution :

const int MODULO = 1000000007;

struct Line
{
	LL a, b, c;

	Line(LL x = 0, LL y = 0, LL z = 0)
	{
		a = x, b = y, c = z;
	}

};

int n, x;
vector<Line> V;
LL wynik, lewo, prawo;

bool porownaj(Line L1, Line L2)
{
	if(L1.a * L2.b < L1.b * L2.a) return true;
	else return false;
}

inline void wLewo(int i)
{
	while(porownaj(V[lewo], V[i]) == true)
	{
		lewo++;
	}
}

inline void wPrawo(int i)
{
	while(porownaj(V[i], V[prawo]) == false)
	{
		if(prawo > n) break;
		else prawo++;
	}
}

int main()
{
	scanf("%d", &n);
	V.resize(n);
	REP(i,n) scanf("%lld %lld %lld", &V[i].a, &V[i].b, &V[i].c);
	sort(ALL(V), porownaj);

	REP(i, n)
	{
		while(porownaj(V[lewo], V[i])) ++lewo;
		while(prawo < n && !porownaj(V[i], V[prawo])) ++prawo;

		wynik += lewo * (n - prawo) % MODULO;
		wynik %= MODULO;
	}

	printf("%lld\n", wynik);

	return 0;
}