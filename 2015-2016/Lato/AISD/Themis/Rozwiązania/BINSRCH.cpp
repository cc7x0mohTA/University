// Bartosz Bednarczyk
// 273 479
// KLO

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int n, k, x;
  scanf("%d", &n);
  vector<int> v(n);

  for(int i = 0; i < n; i++) scanf("%d", &v[i]);

  scanf("%d", &k);
  while(k--) {
    scanf("%d", &x);
    vector<int>::iterator low = lower_bound(v.begin(), v.end(), x);
    printf("%d ", v.end() - low);
  }

  return 0;
}
