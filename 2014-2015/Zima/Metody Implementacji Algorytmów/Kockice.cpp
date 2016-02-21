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

int n;
vector<LL> A, B;

LL f(LL x)	// Wyliczamy funkcje f zgodnie z wzorcowka
{
	LL wynik = 0;

	REP(i,n)
	{
		LL srodek = x + abs(n/2 - i);
		wynik += abs(srodek-A[i]) + abs(srodek-B[i]);
	}

	return wynik;
}

LL Solve(LL l, LL r)	// Binary Search po wyniku
{
	if(l == r) return f(l);

	LL sr = (l+r)/2;

	if(f(sr) < f(sr+1)) return Solve(l, sr);
	else return Solve(sr+1, r);
}

int main()
{
	scanf("%d", &n);
	A.resize(n); B.resize(n);
	REP(i,n) scanf("%d", &A[i]);
	REP(i,n) scanf("%d", &B[i]);

	LL maxh = 0;
	REP(i,n) maxh = max(maxh, max(A[i], B[i]));
	printf("%lld\n", Solve(0, maxh));

	return 0;
}