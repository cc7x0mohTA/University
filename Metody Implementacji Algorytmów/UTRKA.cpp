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
const int INF = 10000000;

// Solution :

struct Matrix
{
	vector<VI> M; int SIZE;

	Matrix(int m = 0)
	{
		M.resize(m); SIZE = m;
		REP(i, m) M[i].resize(m, -INF);
		REP(i, m) M[i][i] = 0;
	}

	Matrix operator* (Matrix&B)
	{
		int n = SIZE; Matrix C(n);

		REP(i, n)
		{
			REP(j, n)
			{
				C.M[i][j] = -INF;

				REP(k, n)
				{
					C.M[i][j] = max(C.M[i][j], M[i][k] + B.M[k][j]);	// zmodyfikowane "mnozenie" macierzy
				}
			}
		}

		return C;
	}
	
	void Print()
	{
		REP(i, SIZE)
		{
			REP(j, SIZE)
			{
				M[i][j] <= -INF ? printf("-oo\t") : printf("%d\t", M[i][j]);
			}

			printf("\n");
		}
	}

	void Trace()
	{
		printf("TRACE:\n");
		REP(i, SIZE) M[i][i] <= -INF ? printf("-oo\t") : printf("%d\t", M[i][i]);
		printf("\n");
	}

	void Load(int k)
	{
		REP(t, k)
		{
			int i, j; scanf("%d %d", &i, &j); i--; j--;
			int x, y; scanf("%d %d", &x, &y);
			int val = y-x;
			M[i][j] = val;
		}
	}

	int Query()
	{
		int q = -1;
		REP(i,SIZE) q = max(q, M[i][i]);
		return q;
	}

	~Matrix() { M.clear(); }
};

Matrix Potegi[11];
Matrix Odp[666];

Matrix Generuj(int k)
{
	//printf("WYWOLANIE DLA K = %d\n", k);

	if(Odp[k].SIZE != 0) return Odp[k];

	if(k == 1) return Potegi[1];
	else
	{
		if(k % 2 == 0)
		{
			Matrix A = Generuj(k/2); return Odp[k] = A * A;
		}
		else
		{
			Matrix A = Generuj((k-1)/2); return Odp[k] = A * A * Potegi[1];
		}
	}
}

int main()
{
	int n, m; scanf("%d %d", &n, &m); Matrix Macierz(n); Macierz.Load(m);

	Potegi[1] = Odp[1] = Macierz;

	FOR(i, 2, 10)
	{
		Potegi[i] = Potegi[i-1] * Potegi[i-1];
		Odp[1 << (i-1)] = Potegi[i];
	}

	Matrix A; int a = -1, b = 1 << 10;

	FOR(i, 1, 9)
	{
		if(Potegi[i].Query() <= 0 && Potegi[i+1].Query() > 0)
		{

			A = Potegi[i]; a = 1 << (i-1); b = 1 << i; 
			break;
		}
	}

	while(a != b)
	{
		int x = (a+b)/2;

		//printf("[a,x,b] = [%d,%d,%d]\n", a, x, b);

		A = Generuj(x);

		if(A.Query() > 0) b = x;
		else a = x+1;
	}

	if(A.Query() <= 0) A = A * Macierz;

	printf("%d %d\n", a, A.Query());

	return 0;
}