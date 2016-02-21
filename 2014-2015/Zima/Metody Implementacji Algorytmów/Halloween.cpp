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
	int T, N; VI V, S;

	scanf("%d %d", &T, &N); V.resize(N+1); S.resize(N+1); S[0] = 0;
	FOR(i,1,N) { scanf("%d", &V[i]); S[i] = S[i-1] + V[i]; }

	while(T--)
	{
		int x, y; scanf("%d %d", &x, &y);
		printf("%d\n", S[y]-S[x-1]);
	}

	return 0;
}