/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <stack>
#include <vector>
#include <cstdio>
using namespace std;

#define FOR(x, b, e) for(int x = b; x <= (e); x++)
#define FORD(x, b, e) for(int x = b; x >= (e); x--)
#define REP(x, n) for(int x = 0; x < (n); x++)
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> pii;

const int INF = 10000000;
const int MAXN = 1000000;

int main()
{
    int n, M; scanf("%d %d", &n, &M);

    VI V[n+5];
    int Preord[n+5], RPreord[n+5];
    int p[n+5]; int m[n+5]; int d[M+5];
    int counter = 0;

    p[0] = 0; m[0] = 0; d[0] = 0;

    //REP(i, M+5)
    for(int i = 1; i < M+5; i++) d[i] = -INF;
    
    //REP(i,n)
    for(int i = 0; i < n; i++)
    {
        int x, y; scanf("%d %d", &x, &y);
        p[i+1] = x;
        V[x].PB(i+1);
        m[i+1] = y;
    }

    stack<int> stos; stos.push(0);
    
    while(stos.empty() == false)
    {
        int w = stos.top(); stos.pop(); Preord[counter] = w; RPreord[w] = counter; counter++;
                
        //REP(i, SIZE(V[w])) 
        for(int i = 0; i < V[w].size(); i++) stos.push((V[w][i]));
    }
    
    //FOR(i,1,n)
    for(int i = 1; i <= n; i++)
    {
        //FORD(j,M,m[Preord[i]])
        for(int j = M; j >= m[Preord[i]]; j--)
        {
            if(d[j-m[Preord[i]]] >= RPreord[p[Preord[i]]]) d[j] = i;
        }
    }
    
    //FORD(i, M, 0)
    for(int i = M; i >= 0; i--)
    {
        if(d[i] != -INF)
        {
            printf("%d\n", i); return 0;
        }
    }
}