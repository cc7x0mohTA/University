/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
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
typedef long long LL;

const double EPS = 10e-9;
const int INF = 1000000001;

// Solution :

int n, k;
map<int, int> Mapa;
VI V, S, T;


void Prepare()
{
	scanf("%d %d", &n, &k);
	V.resize(n); S.resize(n); T.resize(n);

	REP(i, n) scanf("%d", &V[i]);
	REP(i, n) S[i] = V[i];
	sort(S.begin(), S.end()); reverse(S.begin(), S.end());

	int i = 0, counter = 0;

	while(i < n)
	{
		for(int j = i; j < i+k; j++)
		{
			Mapa[S[j]] = counter;
		}

		counter++; i += k;
	}

	T.resize(n);
	REP(j, n) T[j] = Mapa[V[j]];
	reverse(T.begin(), T.end());
}

int lis()
{
	int LongestEndingWith[n];
	int LongestEver = 0;
	for (int i=0; i<n; i += 1)
	{
		LongestEndingWith[i] = 1; 
    	for (int j=0; j<i; j += 1) 
    	{
    		       if (T[j] <= T[i]) LongestEndingWith[i] = max(LongestEndingWith[i], LongestEndingWith[j]+1); 
    	}
	}

    int ans = 0;
    REP(i, n) ans = max(ans, LongestEndingWith[i]);
    return ans;
}


int main()
{
	Prepare();
	
	printf("%d\n", n-lis());

	return 0;
}