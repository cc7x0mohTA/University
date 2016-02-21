/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <iostream>
#include <vector>
#include <algorithm>
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

//inline string IntToStr(int x) { ostringstream ss; ss << x; return ss.str(); }
//inline int StrToInt(string x) { int i; istringstream iss(x); iss >> i; return i; }

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1410065400;

// Solution :

map<char,int> mapa;
vector<int> V;
int suma, wynik;

void Generuj()
{
	int counter = 0;

	for(char znak = 'A'; znak <= 'Z'; znak++)
	{
		if(znak < 'N')
		{
			mapa[znak] = counter;
			counter++;
		}
		else if(znak == 'N')
		{
			mapa[znak] = 13;
			counter = 12;
		}
		else
		{
			mapa[znak] = counter;
			counter--;
		}
	}
}

VI BezA(string s)
{
	V.PB(0);
	REP(i,SIZE(s)-1)
	{
		if(s[i+1] == 'A') continue;
		else V.PB(i+1);
	}

	 V.PB(0); return V;
}

int WynikNaPrzedziale(int x, int y)
{
	return suma + min(x+x+y,y+y+x);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	Generuj();

	int t; cin >> t;

	while(t--)
	{
		V.clear(); suma = 0, wynik = INF;
		string s; cin >> s;
		V = BezA(s);

		REP(i,SIZE(s)) suma += mapa[s[i]];

		REP(i, SIZE(V)-1) wynik = min(wynik, WynikNaPrzedziale(V[i], SIZE(s) - V[(i+1)]));
		wynik = min(wynik, suma + min(V[SIZE(V)-2], SIZE(s)));
		cout << wynik << "\n";
	}

	return 0;
}