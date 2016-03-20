#include <cstdio>
#include <set>
using namespace std;
typedef long long LL;

set<LL> S;

void addToSet(LL value) {
	set<LL>::iterator it = S.find(value);
	
	if(it != S.end()) {
		S.erase(it);
		addToSet(2*value);
	}
	else S.insert(value);
}

int main() {
	
	int m; scanf("%d", &m);

	while(m--) {
		int ile, elem;
		scanf("%d %d", &elem, &ile);
		while(ile--) addToSet(elem);
	}

	printf("%lu\n", S.size());

	return 0;
}