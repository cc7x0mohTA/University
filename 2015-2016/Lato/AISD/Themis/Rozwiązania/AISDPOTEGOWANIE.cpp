// Bartosz Bednarczyk
// 273 479
// KLO

#include <cstdio>
using namespace std;

int fastPow(int a, int b, int m) {
  if(b == 0) return 1;
  if(b == 1) return (a%m);
  long long x = fastPow(a, b/2, m) % m;
  x = (x * x) % m;
  return ((b%2==0) ? x%m : (a*x)%m); 
}

int main() {
  int t; scanf("%d", &t);

  while(t--) {
    int a, b, m; scanf("%d %d %d", &a, &b, &m);
    printf("%d\n", fastPow(a,b,m));
  }

  return 0;
}
