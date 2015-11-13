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

string s;
string Ans[4] = {"00", "01", "10", "11"};
int ile0, ile1, ile_, p, q, kon_, kon1, kon0;

void Prepare()
{
	cin >> s; ile0 = ile1 = ile_ = kon_ = kon1 = kon0 = 0;
	for(int i = 0; i < s.size(); i++) { (s[i] == '1' ? ile1++ : ( s[i] == '0' ? ile0++ : ile_++ )); }
	p = s.size() - s.size() / 2 - 1;
	q = s.size() / 2 - 1;
	( s[s.size()-1] == '?' ? kon_ = 1 : (s[s.size()-1] == '1' ? kon1 = 1 : kon0 = 1) );
}

void Solve()
{
	//cout << "ile0 = " << ile0 << " " << "ile1 = " << ile1 << " ile? = " << ile_ << "\n"; 

	if(p >= ile1) cout << Ans[0] << "\n";
	if(!kon0 && p+1-ile1-kon_ >= 0 && ile1+ile_- p - 1 >= 0) cout << Ans[1] << "\n";
	if (!kon1 && (q + 1 - ile0 - kon_ >= 0) &&  (ile_ + ile0 - 1 - q >= 0)) cout << Ans[2] << "\n";
	if(q >= ile0) cout << Ans[3] << "\n";
}

int main()
{
	std::ios_base::sync_with_stdio(false); cin.tie(0);
	Prepare(); Solve();

	return 0;
}