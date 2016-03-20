// Bartosz Bednarczyk
// 273 479
// KLO

#include <bits/stdc++.h>
using namespace std;

#define REP(x, n) for(int x = 0; x < (n); x++)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define ST first
#define ND second

typedef long long LL;
typedef vector<LL> VLL;
typedef pair<LL, LL> PLL;

// Solution :

int main()
{
	int m; scanf("%d", &m);
	vector<PLL> V(m, {0,0});
	vector<LL> M(m);

	while(m--) {
		LL d, nd;
		scanf("%lld %lld", &d, &nd);
		V[m] = {d,nd};
	}

	LL wynik = 0;
	sort(ALL(V));
	REP(i, SIZE(V)) M[i] = V[i].ST;

	REP(i, SIZE(V)) {
		LL d = V[i].ST, nd = V[i].ND;

		while(nd > 0) {
			if(i+1 == SIZE(V) || d < V[i+1].ST) {
				if(nd % 2 == 1) wynik++;
				nd >>= 1; d <<= 1;
			}
			else if(d == V[i+1].ST) {
				V[i+1].ND += nd; nd = 0;
			}
			else {
				auto it =  lower_bound(M.begin(), M.end(), d);
				auto index = it - M.begin();

				if(V[index].first == d) {
					V[index].second += nd; nd = 0;
				}
				else {
					if(nd % 2 == 1) wynik++;
					nd >>= 1; d <<= 1;
				}
			}

			V[i].ST = -1;
		}
	}

	printf("%lld\n", wynik);
	return 0;
}