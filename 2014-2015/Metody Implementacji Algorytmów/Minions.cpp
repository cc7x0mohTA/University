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
const int INF = 1000000001;

// Solution :

vector<LL> odp;

class FanwickTree	// Z mojego githuba
{

	// Wazne! Numerujemy od 1 do N

	private: std::vector<LL> A, B; int size; // W sumie dwa drzewka
	public:

		FanwickTree(int N) { size = N; A.assign(N+5, 0); B.assign(N+5, 0); }
		
		void Update(LL r, LL d)
		{
			if(r  >= 0)
			{
				for(LL i = r; i >= 0; i = (i&(i+1))-1) B[i] += d;
				for(LL i = r|(r+1); i < size; i|= i+1) A[i] += d*(r-(i&(i+1))+1);
			}
		}

		void RangeUpdate(int a, int b, int v)
		{
			Update(b, v); Update(a-1, -v);
		}

		LL Query(LL r)
		{
			LL w = 0;
			for(LL i = r; i >= 0; i=(i&(i+1))-1) w += A[i] + B[i]*(i-(i&(i+1))+1);
			for(LL i = r|(r+1); i < size; i |= i+1) w += B[i]*(r-(i&(i+1))+1);
			return w;
		}

		LL RangeQuery(LL a, LL b)
		{
			return Query(b) - Query(a-1);
		}
};

struct Krotka
{
	LL t, a, b, val, query;

	Krotka(LL _t = 0, LL _a = 0, LL _b = 0, LL _val = 0, LL _query = 0)
	{
		t = _t; a = _a; b = _b; val = _val; query = _query;
	}

	/*void Print()
	{
		printf("t: %d, a: %d, b : %d, val : %d, query : %d\n", t, a, b, val, query);
	}*/
};

bool Porownaj(Krotka K1, Krotka K2)
{
	if(K1.t == K2.t)
	{
		return K1.query < K2.query;
	}
	else return K1.t < K2.t;
}

int main()
{
	LL n, m, k; scanf("%lld", &n);

	FanwickTree Drzewko(n+1);

	FOR(i, 1, n)
	{
		LL x; scanf("%lld", &x); Drzewko.RangeUpdate(i, i, x);
	}

	scanf("%lld", &m); vector<Krotka> V;

	FOR(i, 1, m)
	{
		LL t, a, d, e; scanf("%lld %lld %lld %lld", &t, &a, &d, &e);

		LL x  = max(1LL,a-d), y = min(n, a+d);

		Krotka K(t,x,y,e,0); V.PB(K);
	}

	scanf("%lld", &k);

	FOR(i,1,k)
	{
		LL t, p, q; scanf("%lld %lld %lld", &t, &p, &q);
		Krotka K(t,p,q,i-1,1); V.PB(K);
	}

	odp.resize(k); sort(ALL(V), Porownaj);


	REP(i, SIZE(V))
	{
		Krotka K = V[i];

		if(V[i].query == 0)
		{
			Drzewko.RangeUpdate(K.a, K.b, K.val);
		}
		else
		{
			LL ans = Drzewko.RangeQuery(K.a, K.b);
			odp[K.val] = ans;

		}
	}

	REP(i, SIZE(odp)) printf("%lld\n", odp[i]);

	return 0;
}