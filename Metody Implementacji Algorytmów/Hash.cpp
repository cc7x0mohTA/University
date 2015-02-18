/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <cstdio>
#include <vector>
using namespace std;

#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); x--)
#define REP(x, n) for(int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const LL INF = 1 << 25;

// Solution :


LL N, K, M, MOD, ans = 0;
int mapa[INF+1];

LL odwrotnosc;

// Obliczanie odwrotnosci modulo P:

vector<LL> euclid(LL a, LL b)
{
	if( b == 0 ) { vector<LL> V; V.PB(a); V.PB(1); V.PB(0); return V; }
	
	vector<LL> V = euclid(b, a % b);

	vector<LL> W; W.PB(V[0]); W.PB(V[2]); W.PB(V[1] - (a/b) * V[2]);
	return W;
}

LL InverseModP(LL a, LL p)
{
	vector<LL> V = euclid(p, a);
	LL y = V[2];
	if(y < 0) y += p;
	return y;
}

// Generowanie haszy 

void Generuj(LL hash, int len)
{
	if(len == 0) mapa[hash]++;
	else
	{
		FOR(i,1,26)
		{
			LL hash2 = hash * 33;
			hash2 ^= i;
			hash2 &= (MOD-1);
			Generuj(hash2, len-1);
		}
	}
}

void GenerowanieOdTylu(LL S, int len)
{
	if(len == 0) ans += mapa[S];
	else
	{
		FOR(i,1,26)
		{
			LL S2 = S^i;
			S2 *= odwrotnosc;
			S2 &= (MOD-1);
			GenerowanieOdTylu(S2, len-1);
		}
	}
}

int main()
{
	scanf("%lld %lld %lld", &N, &K, &M);
	MOD = 1 << M;

	odwrotnosc = InverseModP(33,MOD);

	Generuj(0, N/2); GenerowanieOdTylu(K, N-N/2);
	
	printf("%lld\n", ans);

	return 0;
}