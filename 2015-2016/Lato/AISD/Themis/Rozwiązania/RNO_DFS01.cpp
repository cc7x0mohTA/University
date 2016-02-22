// Bartosz Bednarczyk
// 273 479
// KLO

#include <cstdio>
#include <vector>
using namespace std;

int n, m;
vector< vector<int> > v;
vector<int> w, visited;

void oblicz(int nr) {
  visited[nr] = 1;
  for(int i = 0; i < v[nr].size(); i++) {
    if(visited[ v[nr][i] ] == 0) {  
      oblicz(v[nr][i]);
      w[nr] += w[v[nr][i]];
    }
  }
  w[nr]++;
}

int main() {
  scanf("%d %d", &n, &m);
  v.resize(n+1);
  w.resize(n+1, 0);
  visited.resize(n+1, 0);

  while(m--) {
    int x, y; scanf("%d %d", &x, &y);
    v[x].push_back(y);
    v[y].push_back(x);
  }

  oblicz(1);

  for(int i = 1; i <= n; i++) printf("%d ", w[i]); 

  return 0;
}
