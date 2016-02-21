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

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1000000001;
const int MAXN = 1000;

struct Circle
{
	int x, y, r;

	Circle(int _x = 0, int _y = 0, int _r = 0) { r = _r; y = _y; x = _x; }

	void Print()
	{
		printf("[%d, %d] R: %d\n", x,y,r);
	}

	bool CzyZawiera(int _x, int _y)
	{
		LL X = _x, AX = x, Y = _y, AY = y, R = r;
		LL dist = (X-AX)*(X-AX) + (Y-AY)*(Y-AY);
		LL RR = R*R;

		if(dist < RR) return true;
		else return false;
	}
};

int n, m, k;

vector<pii> Punkty;
vector<Circle> Okregi;
std::bitset<MAXN> Zawieranie[MAXN+5]; // [punkt][okrag]

int Query(int x, int y)
{
	bitset<MAXN> w = Zawieranie[x] ^ Zawieranie[y];
	return w.count();
}

void Prepare()
{
	scanf("%d %d %d", &n, &m, &k);
	Punkty.resize(n); Okregi.resize(m);

	REP(i, n)
	{
		int x, y; 
		scanf("%d %d", &x, &y);
		Punkty[i] = pii(make_pair(x,y));
	}

	REP(i, m)
	{
		int r, x, y;
		scanf("%d %d %d", &r, &x, &y);
		Okregi[i] = Circle(x, y, r);
		//Okregi[i].Print();
	}

	REP(i, n) REP(j, m)
	{
		Zawieranie[i][j] = Okregi[j].CzyZawiera(Punkty[i].ST, Punkty[i].ND);
	}
}

int main()
{
	Prepare();

	REP(i, k)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		x--; y--;
		int w = Query(x,y);

		printf("%d\n", w);
	}

	return 0;
}