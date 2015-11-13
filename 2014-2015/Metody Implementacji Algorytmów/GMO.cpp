#include <iostream>
#define min(a,b) ((a) < (b) ? (a) : (b))
using namespace std;

string S, R;
int cA, cC, cG, cT, ans = 99999999;


void Prepare()
{
	cin >> S >> R >> cA >> cC >> cG >> cT;
	S += "#";
}

int CostOf(char c)
{
	if(c == 'A') return cA;
	else if(c == 'C') return cC;
	else if(c == 'G') return cG;
	else return cT;
}

void Solve()
{
	for(int i = 0; i < S.size()-1; i++)
	{
		int cost = 0, posR = 0, posS = i;

		while(posR < R.size())
		{
			if(S[posS] == R[posR]) posR++, posS++;
			else cost += CostOf(R[posR]), posR++;
		}

		ans = min(ans, cost);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false); cin.tie(0);

	Prepare();
	Solve();
	cout << ans << "\n";

	return 0;
}