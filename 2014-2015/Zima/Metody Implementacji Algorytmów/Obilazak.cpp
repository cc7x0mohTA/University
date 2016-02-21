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

int k, x; VI V;
VI Level[11];

void Solve(int lev, VI Seq)
{
	VI S1, S2; int n = Seq.size();

	if(n == 1)
	{
		Level[lev].PB(Seq[0]);
		return;
	}

	for(int i = 0; i < n; i++)
	{
		int value = (n-1)/2;

		if(i < value) S1.PB(Seq[i]);
		else if(i > value) S2.PB(Seq[i]);
		else Level[lev].PB(Seq[i]);
	}

	Solve(lev+1, S1); Solve(lev+1, S2);
}

int main()
{
	scanf("%d", &k);

	for(int i = 1; i < (1<<k); i++) scanf("%d", &x), V.push_back(x);

	Solve(1, V);

	FOR(i,1,k)
	{
		REP(j, (int)Level[i].size()) printf("%d ", Level[i][j]);
		printf("\n");
	}

	return 0;
}