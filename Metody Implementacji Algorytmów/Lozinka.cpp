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

int n;
map<string, int> Mapa;
vector<string> V;

int main()
{
	cin >> n;

	REP(i, n)
	{
		string s; cin >> s;
		string y = s; reverse(ALL(y)); 
		V.push_back(s);
		Mapa[s]++;
	}

	string answer = "";

	REP(i,n)
	{
		string r = V[i]; reverse(ALL(r));
		if(Mapa[r] >= 1 && Mapa[V[i]] >= 1) { answer = V[i]; break; }
	}

	cout << answer.size() << " " << answer[answer.size()/2] << "\n";

	return 0;
}
