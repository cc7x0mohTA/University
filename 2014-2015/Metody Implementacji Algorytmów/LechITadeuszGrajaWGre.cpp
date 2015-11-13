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

LL a, b, c, n, x, y, z;
vector<char> Odp;

void Generuj()	// generowanie odpowiedzi z omowienia zadania
{
	a = b = 0;

	while (a < x || b < y)
	{
		if( (a+1) * y > (b+1) * x ){ b++; Odp.PB('T'); }
		else if( (a+1) * y < (b+1) * x ) { a++; Odp.PB('L'); }
		else { a++; b++; Odp.PB('O'); Odp.PB('O'); }
	}
}

void Odpowiedz()
{
	while(n--)
	{
		cin >> z;
		char ans = Odp[ (z-1) % (x+y) ];

		if(ans == 'L') cout << "Lech\n";
		else if(ans == 'T') cout << "Tadeusz\n";
		else cout << "Obaj\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> x >> y;

	Generuj();
	Odpowiedz();

	return 0;
}