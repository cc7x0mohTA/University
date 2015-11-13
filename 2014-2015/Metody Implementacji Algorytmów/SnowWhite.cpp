/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <cstdio>
#include <vector>
#include <algorithm>
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

class MaxTree
{
	private: vector<int> w; int M;	// M = 2^k. Przedział [0...M-1]
	public:

			MaxTree(int m) { M = m; w.assign(2*M+5, 0); }	// Tworzymy tablicę zamiast drzewa

			void Insert(int x, int val)
			{
				int v = M + x;  w[v] = val;
				while(v != 1) { v /= 2;  w[v] = max(w[2*v],w[2*v + 1]); } // Update na ścieżce
			}

			int Query(int a, int b) // Suma z przedziału [a,b]
			{
				int va = M+a, vb = M+b, wynik = w[va];
				if(va != vb) wynik = max(wynik, w[vb]);
			
				while(va/2 != vb/2)
				{
					if(va % 2 == 0) wynik = max(wynik, w[va+1]); // Prawa bombka na lewej ścieżce
					if(vb % 2 == 1) wynik = max(wynik, w[vb-1]); // Lewa bombka na prawej ścieżce
					va /= 2; vb /= 2;
				}

				return wynik;
			}
};

class MinTree
{
	private: vector<int> w; int M;	// M = 2^k. Przedział [0...M-1]
	public:

			MinTree(int m) { M = m; w.assign(2*M+5, 0); }	// Tworzymy tablicę zamiast drzewa

			void Insert(int x, int val)
			{
				int v = M + x;  w[v] = val;
				while(v != 1) { v /= 2;  w[v] = min(w[2*v],w[2*v + 1]); } // Update na ścieżce
			}

			int Query(int a, int b) // Suma z przedziału [a,b]
			{
				int va = M+a, vb = M+b, wynik = w[va];
				if(va != vb) wynik = min(wynik, w[vb]);
			
				while(va/2 != vb/2)
				{
					if(va % 2 == 0) wynik = min(wynik, w[va+1]); // Prawa bombka na lewej ścieżce
					if(vb % 2 == 1) wynik = min(wynik, w[vb-1]); // Lewa bombka na prawej ścieżce
					va /= 2; vb /= 2;
				}

				return wynik;
			}
};

int main()
{
	int n, m; scanf("%d %d", &n, &m);
	MaxTree MaxT(2*n); MinTree MinT(2*n);
	VI V(n+5); REP(i, n) scanf("%d", &V[i]);

	REP(i, n)
	{
		V[i]--;
		MinT.Insert(V[i], i);
		MaxT.Insert(V[i], i);
	}

	while(m--)
	{
		int x,y,z; scanf("%d %d %d", &x, &y, &z);
		y--; z--;

		if(x == 1) // zamiana miejscami krasnali na miejscach 
		{
			int a = V[y], b = V[z];
			swap(V[y], V[z]);
			MinT.Insert(a,z); MinT.Insert(b, y);
			MaxT.Insert(a,z); MaxT.Insert(b,y);
		}
		else
		{
			int ans = MaxT.Query(y,z) - MinT.Query(y,z)+1;
			int dlg = z-y+1;
			if(ans == dlg) printf("YES\n");
			else printf("NO\n");			
		}
	}

	return 0;
}