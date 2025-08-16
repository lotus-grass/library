/*
  Prob: synch
  Author: K.F.Cat
  Date: 16-04-07 08:47
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 500001;

long n, m;
long i;
long edge[maxn << 1][3], pos[maxn], ok[maxn];
long long max[maxn];
long long ans;

void sort(long l, long r)
{
     long i, j, k;
     long x, t;
     
     i = l;
     j = r;
     x = edge[(i + j) >> 1][0];
     while (i < j)
     {
           while (edge[i][0] < x)
                 i ++;
           while (edge[j][0] > x)
                 j --;
           if (i <= j)
           {
              for (k = 0; k < 3; k ++)
              {
                  t = edge[i][k];
                  edge[i][k] = edge[j][k];
                  edge[j][k] = t;
              }
              i ++;
              j --;
           }
     }
     if (i < r)
        sort(i, r);
     if (l < j)
        sort(l, j);
}

void dfs(long cur, long long len)
{
     long i;
     long next, f = 0;
     long long totlen, help;
     
     ok[cur] = 1;
     max[cur] = len;
     for (i = pos[cur]; i < pos[cur + 1]; i ++)
         if (ok[edge[i][1]] == 0)
         {
            next = edge[i][1];
            totlen = len;
            totlen += edge[i][2];
            dfs(next, totlen);
            if (max[cur] < max[next])
            {
               help = max[next];
               help -= max[cur];
               help *= i - pos[cur] - f;
               ans += help;
               max[cur] = max[next];
            }
            else
            {
                help = max[cur];
                help -= max[next];
                ans += help;
            }
         }
         else
             f = 1;
}

int main()
{
    freopen("synch.in", "r", stdin);
    freopen("synch.out", "w", stdout);
    
    scanf("%d", &n);
    scanf("%d", &m);
    for (i = 1; i < n; i ++)
    {
        scanf("%d %d %d", &edge[i][0], &edge[i][1], &edge[i][2]);
        edge[i + n - 1][0] = edge[i][1];
        edge[i + n - 1][1] = edge[i][0];
        edge[i + n - 1][2] = edge[i][2];
    }
    
    sort(1, (n - 1) << 1);
    edge[0][0] = -1;
    for (i = 1; i <= (n - 1) << 1; i ++)
        if (edge[i][0] > edge[i - 1][0])
           pos[edge[i][0]] = i;
    pos[n + 1] = (n << 1) - 1;
    
    memset(ok, 0, sizeof ok);
    ans = 0;
    dfs(m, 0);
    
/*    for (i = 1; i <= n; i ++)
        printf("%I64d ", max[i]);
    printf("\n");*/
    printf("%I64d\n", ans);
    
    return 0;
}
