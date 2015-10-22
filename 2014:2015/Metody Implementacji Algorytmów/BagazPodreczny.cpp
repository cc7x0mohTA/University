/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
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
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1000000001;


inline void readINT(int *n)
{
	register char c = 0;
	while (c < 33) c = fgetc_unlocked(stdin);
	(*n) = 0;
	while (c>32) {(*n)=(*n)*10 + (c-'0'); c=fgetc_unlocked(stdin);}
}


class SegmentTree // Drzewo przedziałowe punkt-przedział (z sumą)
{
	private: vector<int> w; int M;	// M = 2^k. Przedział [0...M-1]
	public:

			SegmentTree(int m) { M = m; w.assign(2*M+5, 0); }	// Tworzymy tablicę zamiast drzewa

			void Insert(int x, int val)
			{
				int v = M + x;  w[v] += val;
				while(v != 1) { v /= 2;  w[v] = w[2*v] + w[2*v + 1]; } // Update na ścieżce
			}

			int Query(int a, int b) // Suma z przedziału [a,b]
			{
				int va = M+a, vb = M+b, wynik = w[va];
				if(va != vb) wynik += w[vb];
			
				while(va/2 != vb/2)
				{
					if(va % 2 == 0) wynik += w[va+1]; // Prawa bombka na lewej ścieżce
					if(vb % 2 == 1) wynik += w[vb-1]; // Lewa bombka na prawej ścieżce
					va /= 2; vb /= 2;
				}

				return wynik;
			}
};

struct Triple
{
	int x, y;
	bool firma;

	Triple(int xx = 0, int yy = 0, bool f = false)
	{
		x = xx; y = yy; firma = f;
	}
};

bool Porownaj(Triple A, Triple B)	// false gdy < 
{
	if(A.x == B.x && A.y == B.y && B.firma == true) return false;

	if(A.x < B.x) return true;
	else if(A.x == B.x)
	{
		if(A.firma && B.firma)
		{
			if(A.y < B.y) return true;
			else return false;
		}
		else if(A.firma) return true;
		else
		{
			if(A.y <= B.y) return true;
			else return false;
		}
	}
	else return false;
}

map< pii, int > Mapa;
int n, m, maxh;
vector< pair< int, pair<int,int> > > V;
vector<pii> Firmy;

int main()
{
	readINT(&n); readINT(&m);
	//scanf("%d %d", &n, &m);
	vector< pair< int, pair<int,int> > > V;

	REP(i, n)
	{
		int x, y;
		readINT(&x); readINT(&y);
		//scanf("%d %d", &x, &y);
		V.PB(make_pair(x, make_pair(y,1)));
		maxh = max(maxh, y);
	}

	REP(i, m)
	{
		int x, y;
		readINT(&x); readINT(&y);
		//scanf("%d %d", &x, &y);
		V.PB(make_pair(x, make_pair(y,0)));
		maxh = max(maxh, y);
		Firmy.PB(make_pair(x,y));
	}

	sort(ALL(V));

	int SHIFT = 1;

	while(SHIFT < maxh) SHIFT *= 2;

	SegmentTree Drzewo(SHIFT);

	FORD(i, SIZE(V)-1, 0)
	{
		if(V[i].ND.ND == 0)
		{
			int ans = Drzewo.Query(V[i].ND.ST, maxh);
			Mapa[make_pair(V[i].ST, V[i].ND.ST)] = ans;
		}
		else
		{
			Drzewo.Insert(V[i].ND.ST, 1);
		}
	}

	REP(i, Firmy.size())
	{
		printf("%d\n", Mapa[Firmy[i]]);
	}

	return 0;
}