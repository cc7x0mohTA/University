/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
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
const LL INF = 9999999999999999;

// Solution :

vector<int> ceny;
vector<LL> sumy;
vector< pair<LL,LL> > Ostatnie, Nastepne;

int n, t;
LL parz, nieparz;

void SumyPrefiksowe()
{
	sumy.resize(n+2); sumy[n+1] = 0;
	FORD(i, n, 0) sumy[i] = sumy[i+1] + ceny[i];
}

void ObliczOstatnie()	// parz - ND
{
    nieparz = -INF, parz = -INF;

    FOR(i, 1, n)
    {
        Ostatnie[i].ST = nieparz;
        Ostatnie[i].ND = parz;
        ceny[i] % 2 == 0 ? parz = ceny[i] : nieparz = ceny[i];
    }
}

void ObliczNastepne()
{
    nieparz = INF, parz = INF;

    FORD(i,n,1)
    {
        ceny[i] % 2 == 0 ? parz = ceny[i] : nieparz = ceny[i];
        Nastepne[i].ST = nieparz;
        Nastepne[i].ND = parz;
    }
}


void Prepare()
{
	scanf("%d", &n);
    ceny.resize(n+1); Nastepne.resize(n+1); Ostatnie.resize(n+1);

	FOR(i,1,n) scanf("%d", &ceny[i]);
	
    ceny[0] = -1; sort(ALL(ceny));
	
    SumyPrefiksowe();
	ObliczOstatnie();
	ObliczNastepne();
}

LL Query(int k)
{
    int I = n - k + 1;

    if(sumy[I] % 2 == 1) return sumy[I];
    else
    {
        LL w = max(-1ll, max(sumy[I] - Nastepne[I].ST + Ostatnie[I].ND, sumy[I] - Nastepne[I].ND + Ostatnie[I].ST) );
        LL ans = 0;
        w == -1 ? ans = -1 : ans = w;
        return ans;
    }
}

int main()
{
	Prepare(); scanf("%d", &t);

	while(t--)
	{
		int k; scanf("%d", &k); printf("%lld\n", Query(k));
	}

	return 0;
}