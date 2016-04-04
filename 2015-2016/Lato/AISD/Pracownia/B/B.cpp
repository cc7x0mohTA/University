// Bartosz Bednarczyk
// 273 479
// KLO

#include <bits/stdc++.h>
using namespace std;

#define FOR(x, b, e) for(int x = b; x <= (e); x++)
#define REP(x, n) for(int x = 0; x < (n); x++)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
typedef long long LL;
typedef vector<LL> VI;

// Solution :

int W, K;
char buffer[5100];
LL pow7[10] = {1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607};

inline VI readVector() {
	scanf("%s", buffer);
	VI vec(W+6, 0);
	REP(i, W) vec[i+3] = pow7[ (int) buffer[i] - (int) '0'];
	return vec;
}

inline void printVector(VI &vec) {
	FOR(i, 3, W+2) printf("%lld\t", vec[i]);
	printf("\n");
}

inline void op1(VI &u, VI &v, VI &orgv) {
	FOR(i, 3, W+2) {
		v[i] = orgv[i] + max(u[i-1], u[i+1]);
	}
}

inline void op2(VI &u, VI &v, VI &orgv) {
	FOR(i, 3, W+2) {
		v[i] = max(v[i], max(u[i-2], u[i+2])+orgv[i]);
	}
}

int main()
{
	scanf("%d %d", &K, &W);

	VI vec[4];
	VI org[4];

	FOR(i, 0, 2) org[i] = readVector();
	FOR(i, 1, 2) vec[i].resize(W+6, 0);
	vec[0] = org[0];

	 if(K == 3) {
		op1(vec[0], vec[2], org[2]);
		op2(vec[2], vec[1], org[1]);
	}
	else {
		REP(i, K-3) {
			vec[3] = org[3] = readVector();

			op1(vec[0], vec[2], org[2]);
			op2(vec[2], vec[1], org[1]);
			op1(vec[1], vec[3], org[3]);
			op2(vec[3], vec[2], org[2]);

			vec[0] = vec[1]; vec[1] = vec[2]; vec[2] = vec[3];
			org[0] = org[1]; org[1] = org[2]; org[2] = org[3];
		}
	}

	printf("%lld", *max_element(ALL(vec[2])));
	return 0;
}
