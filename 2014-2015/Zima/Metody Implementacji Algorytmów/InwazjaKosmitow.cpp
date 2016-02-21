/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <cstdio>
#include <algorithm>
#include <vector>
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

typedef vector<int> VI;
typedef unsigned long long LL;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1000000001;

// Solution:

LL n;
vector<LL> V, D;

int main()
{
	scanf("%llu", &n); V.resize(n+1); D.resize(n+1);

	REP(i, n) scanf("%llu", &V[i]);

	if(n < 3)
	{
		if(n == 1) printf("%llu\n", V[0]);
		if(n == 2) printf("%llu\n", max(V[0],V[1]));
		return 0;
	}

	D[0] = V[0]; D[1] = V[1]; D[2] = V[2] + V[0];
	FOR(i, 3, n-1) D[i] = max(V[i]+D[i-2], V[i] + D[i-3]);
	printf("%llu\n", max(D[n-1], D[n-2]));

	return 0;
}