// Bartosz Bednarczyk
// 273 479
// KLO

#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
  int a, b;
  scanf("%d %d", &a, &b);
  if(b < a) swap(a,b);
  for(int i = a; i <= b; i++) printf("%d\n", i);
  return 0;
}