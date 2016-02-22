// Bartosz Bednarczyk
// 273 479
// KLO

#include <cstdio>
#include <vector>

using namespace std;

int n, m, k, time;
vector< vector<int> > up, down;
vector<int> in, out;

void DFS(int x) {
		in[x] = time++;
		for(int i = 0; i < down[x].size(); i++) DFS(down[x][i]);
		out[x] = time++;
}

bool query(int x, int y) {
	return (in[x] < in[y] && out[y] < out[x]);
}

int main() {
  scanf("%d %d", &n, &m);
  up.resize(n+1);
  down.resize(n+1);
	in.resize(n+1);
	out.resize(n+1); 

  while(m--) {
  	int x, y;
		scanf("%d %d", &x, &y);
    down[x].push_back(y);
    up[y].push_back(x);
  }

  vector<int> roots;

  for(int i = 1; i <= n; i++) {
    if(up[i].size() == 0) roots.push_back(i);
  }

  for(int i = 0; i < roots.size(); i++) DFS(roots[i]);

	int k; scanf("%d", &k);

	while(k--) {
		int x, y;
		scanf("%d %d", &x, &y);
		if(query(x,y)) printf("TAK\n");
    else printf("NIE\n");
  }

  return 0;
}
