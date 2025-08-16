/*
  Prob: matrix
  Author: K.F.Cat
  Date: 16-04-07 08:18
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 201;

long n, m;
long i, j, k;
long map[maxn][maxn], ok[maxn], p[maxn];
long f, tot;

void dfs(long root)
{
     long i;
     long t;
     
     for (i = 1; i <= n; i ++)
         if (ok[i] == 0 && map[root][i] == 1)
         {
            if (p[i] == 0)
            {
               p[i] = root;
               f = 1;
               return;
            }
            ok[i] = 1;
            t = p[i];
            p[i] = root;
            dfs(t);
            if (f == 1)
               return;
            p[i] = t; 
         }
}

int main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    
    scanf("%d", &m);
    for (i = 1; i <= m; i ++)
    {
        scanf("%d", &n);
        for (j = 1; j <= n; j ++)
            for (k = 1; k <= n; k ++)
                scanf("%d", &map[j][k]);
        
        memset(p, 0, sizeof p);
        for (j = 1; j <= n; j ++)
        {
            memset(ok, 0, sizeof ok);
            f = 0;
            dfs(j);
            tot += f;
            if (f == 0)
               break;
        }
        if (f == 0)
           printf("No\n");
        else
            printf("Yes\n");
    }
    
    return 0;
}
