#include <cstdio>
#include <algorithm>
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
typedef long long LL;

const double EPS = 10e-9;
const int INF = 1000000001;
const LL MOD = 1000000007LL;

// Solution :

class Matrix
{
	public:
	LL M[2][2];

	Matrix(LL A[2][2])
	{
		REP(I,2) REP(J,2) M[I][J] = A[I][J];
	}
};

Matrix multiply(Matrix A, Matrix B)
{
	LL t[2][2] = {0}; Matrix Res(t);
	REP(I,2) REP(J,2) REP(K,2) Res.M[I][J] += (A.M[I][K]*B.M[K][J]) % MOD, Res.M[I][J] %= MOD;
	return Res;
}

Matrix power(Matrix A, int n)
{
	if(n == 1) return A;
	else
	{
		LL t[2][2] = {0};
		Matrix Temp = multiply(A, A);
		Temp = power(Temp, n / 2);
		if(n % 2 == 1) Temp = multiply(Temp, A);
		return Temp;
	}
}

LL ways(int n, int k)	// Uogolnione na dowolny sympleks
{
	if(n == 1) return 0;
	else
	{
		LL Base[2][2] = {{k-1,k}, {1,0}};
		Matrix BASE(Base);
		Matrix A = power(BASE, n);
		return A.M[1][1] % MOD;
	}
}

int main()
{
	int n, k; scanf("%d %d", &n, &k);
	printf("%lld", ways(n, k));
	return 0;
}