// Bartosz Bednarczyk
// 273 479
// KLO

#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int x, y;
	scanf("%d %d", &x, &y);
	if(x % 2 == 0) x++;

	for(int i = x; i <= y; i += 2) printf("%d ", i);

	return 0;
}