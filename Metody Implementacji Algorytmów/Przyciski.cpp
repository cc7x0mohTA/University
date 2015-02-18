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

int main()
{
	int n, m, x, maks = 0, mini = 0;
	scanf("%d %d", &n, &m);
	VI V(n+1, 0);

	while(m--)
	{
		scanf("%d", &x);

		if(x == n+1) mini = maks;
		else
		{
			if(V[x] < mini) V[x] = mini;
			V[x]++;
			if(V[x] > maks) maks = V[x];
		}
	}

	FOR(i,1,n)
	{
		if(V[i] < mini) V[i] = mini;
	}
	FOR(i,1,n) printf("%d ", V[i]);

	return 0;
}