/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <cstdio>
#include <vector>
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
typedef unsigned long long LL;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1000000001;
const int MX = 1000000;

// Solution :

LL V[MX+5]; int N, M;

inline void readLONG(LL *n)
{
	register char c = 0;
	while (c < 33) c = fgetc_unlocked(stdin);
	(*n) = 0;
	while (c>32) {(*n)=(*n)*10 + (c-'0'); c=fgetc_unlocked(stdin);}
}


bool Check(LL value, int n)
{
	int counter = 0;

	REP(i, N)
	{
		counter += (V[i] / value);
		if(counter >= n) return true;
	}

	if(counter >= n) return true;
	else return false;
}

LL BinSearch(LL a, LL b, int n)
{
	//printf("\t(%llu %llu)\t\n", a,b);

	if(b < a) return INF;

	if(a == b) return a;
	else
	{
		LL x = (b-a+1)/2;
		LL y = a+x;

		if(Check(y, n)) return BinSearch(y,b,n);
		else return BinSearch(a,y-1,n);
	}
}

int main()
{
	scanf("%d %d", &N, &M);
	LL suma = 0;
	REP(i, N) readLONG(&V[i]), suma += V[i];

	printf("%llu\n", BinSearch(0, suma, M));

	return 0;
}