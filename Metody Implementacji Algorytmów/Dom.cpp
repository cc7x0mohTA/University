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
const int MAXV = 100000;

// Solution :

const int CZARNY = 2, SZARY = 1, BIALY = 0;

vector<int> V[MAXV+5];
vector<int> deg;
char Color[MAXV+5];
bool cykl = false;
int ile = -1;

void DFS(int u)
{
    Color[u] = SZARY;
    
    REP(i, V[u].size())
    {
        int vertex = V[u][i];
        
        if(Color[vertex] == BIALY) DFS(vertex);
        else if(Color[vertex] == SZARY) cykl = true;
    }
    
    Color[u] = CZARNY; ile++;
}

int main()
{
	int n, m, k; scanf("%d %d %d", &n, &m, &k);

	deg.resize(m+1, 0); k--;

	REP(i, n)
	{
		int x, y; scanf("%d %d", &x, &y); x--; y--;

		if(deg[y] > 0) continue;
		else
		{
			deg[y]++;
			V[y].PB(x);
		}
	}

	DFS(k);

	if(cykl) printf("-1\n");
	else printf("%d\n", ile);

	return 0;
}