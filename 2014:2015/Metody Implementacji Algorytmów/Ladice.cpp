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
const int MAXL = 300000;

// Solution :

class FindUnion // Find Union z mojego /Githuba
{
	private: vector<int> p;
	public:

		FindUnion(int N)
		{
			p.assign(N,0);
			REP(i, N) p[i] = i;	
		}

		int FindSet(int i)
		{
			if(p[i] == i) return i;
			else
			{
				p[i] = FindSet( p[i] );
				return p[i];
			}
		}

		void UnionSet(int i, int j)
		{
			printf("LADICA\n");
			int x = FindSet(i), y = FindSet(j);
			p[x] = p[y];
		}
};

bool T[MAXL+5];

int main()
{
	int N, L; scanf("%d %d", &N, &L);
	FindUnion FU(L+1);

	REP(i,max(L,N)+5) T[i] = false;

	REP(i, N)
	{
		int x, y; scanf("%d %d", &x, &y);

		if(T[x] == false) T[x] = true, FU.UnionSet(x,y);
		else if(T[y] == false) T[y] = true, FU.UnionSet(y,x);
		else if(T[FU.FindSet(x)] == false) T[FU.FindSet(x)] = true, FU.UnionSet(x,y);
		else if(T[FU.FindSet(y)] == false) T[FU.FindSet(y)] = true, FU.UnionSet(y,x);
		else printf("SMECE\n");
	}

	return 0;
}
