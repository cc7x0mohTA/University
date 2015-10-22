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
const int INF = 1000000999;
const int MAXN = 500;

// Solution:

bool visited[MAXN+2][MAXN+2], plansza[MAXN+2][MAXN+2], czykraw[MAXN+2][MAXN+2]; /* X to 1, . to 0 */
int spojna[MAXN+5][MAXN+5];

bool viz[MAXN+5]; int d[MAXN+5];

vector<int> V[MAXN+2];
int h, w, ileV;

void WyswietlPlansze()
{
	REP(i, h)
	{
		REP(j, w) printf("%d", (int)plansza[i][j]);
		printf("\n");
	}
}

void WyswietlSpojne()
{
	REP(i, h)
	{
		REP(j, w) printf("%d\t", spojna[i][j]);
		printf("\n");
	}
}

void WyswietlGraf()
{
	REP(i, ileV)
	{
		printf("%d :\t", i);

		REP(j, V[i].size()) printf("%d\t", V[i][j]);

		printf("\n");
	}
}

void DFS(int i, int j, bool color, int nr)
{
	//printf("[%d %d]\n", i,j);
	visited[i][j] = true;
	spojna[i][j] = nr;

	if(i-1 >= 0 && plansza[i-1][j] == color && visited[i-1][j] == false) DFS(i-1,j,color,nr);
	if(i+1 < h && plansza[i+1][j] == color && visited[i+1][j] == false) DFS(i+1,j,color,nr);

	if(j+1 < w && plansza[i][j+1] == color && visited[i][j+1] == false) DFS(i,j+1,color,nr);
	if(j-1 >= 0 && plansza[i][j-1] == color && visited[i][j-1] == false) DFS(i,j-1,color,nr);
}

inline void LiczSpojne()
{
	ileV = 0;

	REP(i, h) REP(j,w)
	{
		if(visited[i][j] == false)
		{
			DFS(i, j, plansza[i][j], ileV);
			ileV++;
		}
	}

	//cout << "JEST " << ileV << " wierzcholkow w grafie\n";
}

inline void WczytajPlansze()
{
	cin >> h >> w;

	REP(i, h)
	{
		string s; cin >> s;
		REP(j, w) plansza[i][j] = (s[j] == 'X' ? 1 : 0);
	}
}

inline void LiczKrawedzie()
{
	REP(i, ileV) REP(j, ileV) czykraw[i][j] = false;

	REP(i, h) REP(j, w)
	{
		if(j+1 < w && spojna[i][j] != spojna[i][j+1] && czykraw[spojna[i][j]][spojna[i][j+1]] == false)
		{
			czykraw[spojna[i][j]][spojna[i][j+1]] = 1;
			czykraw[spojna[i][j+1]][spojna[i][j]] = 1;
			V[spojna[i][j]].PB(spojna[i][j+1]);
			V[spojna[i][j+1]].PB(spojna[i][j]);
			
		}

		if(i + 1 < h && spojna[i][j] != spojna[i+1][j] && czykraw[spojna[i][j]][spojna[i+1][j]] == false)
		{
			czykraw[spojna[i][j]][spojna[i+1][j]] = 1;
			czykraw[spojna[i+1][j]][spojna[i][j]] = 1;
			V[spojna[i][j]].PB(spojna[i+1][j]);
			V[spojna[i+1][j]].PB(spojna[i][j]);
		}
	}
}

void BFS(int a)
{
  queue<int> Q;
  Q.push(a); viz[a] = true; // wstaw wierzchołek 'a' do kolejki
  d[a] = 0;
  while( !Q.empty() )
  {
    int u = Q.front(); Q.pop();
    for (int i=0; i<V[u].size(); i++)
    {
      int v = V[u][i];
      if ( viz[v]==false )
      {
	Q.push(v); viz[v] = true;
	d[v] = d[u]+1;
      }
    }
  }
}

int Solve()
{
	int wynik = INF;

	REP(i, ileV)
	{
		REP(j, ileV) d[j] = INF, viz[j] = false;
		BFS(i);

		int pom = -1;
		REP(j, ileV) pom = max(pom,d[j]);
		wynik = min(wynik, pom);
	}

	return wynik;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(0);

	WczytajPlansze(); LiczSpojne(); LiczKrawedzie();

	//WyswietlPlansze(); WyswietlSpojne(); 
	//WyswietlGraf(); printf("\n");

	int wynik = Solve(); printf("%d\n", wynik);

	return 0;
}