// Bartosz Bednarczyk
// 273 479
// KLO

#include <vector>
#include <cstdio>
using namespace std;

vector<long long> multiplyMatrixModM(vector<long long> a, vector<long long> b, int m) {
  vector<long long> c(4);
  c[0] = (b[0] * a[0] + a[1] * b[2]) % m;
  c[1] = (b[1] * a[0] + a[1] * b[3]) % m;
  c[2] = (b[0] * a[2] + a[3] * b[2]) % m;
  c[3] = (b[1] * a[2] + b[3] * a[3]) % m;
  return c;
}

vector<long long> fastMatrixPow(vector<long long> a, int n, int m) {

  if(n == 0) {
    a[0] = a[3] = 1;
    a[1] = a[2] = 0;
    return a;
  }
  else if(n == 1) return a;

  vector<long long> b = fastMatrixPow(a, n/2, m);

  if(n % 2 == 0) return multiplyMatrixModM(b,b,m);
  else return multiplyMatrixModM(a, multiplyMatrixModM(b,b,m), m);
}

int fastFibb(int n, int m) {
  vector<long long> a(4, 1); a[3] = 0;
  a = fastMatrixPow(a, n, m);
  return a[2];
}

int main() {
  int t; scanf("%d", &t);

  while(t--) {
    int n, m; scanf("%d %d", &n, &m);
    printf("%d\n", fastFibb(n, m));
  }

  return 0;
}
