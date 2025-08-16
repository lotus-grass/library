/*
  Prob: winner
  Author: K.F.Cat
  Date: 12-04-07 11:16
  Description: ¼ÌÐøÂÒµ·... 
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 301;

long n, m, s = 0;
long i, j;
long map[maxn][maxn], inf[maxn], cur[maxn];
long ans, temp;
long f, a, b;

void dfs(long deep, long base)
{
     long i, j;
     
     if (deep == n + 1)
     {
        temp = 0;
        for (i = 1; i < n; i ++)
            for (j = i + 1; j <= n; j ++)
                if (map[i][j] == 1 && cur[i] != cur[j])
                   temp ++;
        if (base + temp < ans)
           ans = base + temp;
        return;
     }
     
     dfs(deep + 1, base);
     if (map[deep][0] > 0)
     {
        cur[deep] = 1 - cur[deep];
        dfs(deep + 1, base + 1);
        cur[deep] = 1 - cur[deep];
     }
}

void greedy()
{
     long i, j;
     
     f = 0;
     while (f == 0)
     {
           f = 1;
           for (i = 1; i <= n; i ++)
           {
               cur[i] = 1 - cur[i];
               temp = 1;
               if (cur[i] == inf[i])
                  temp = -1;
               for (j = 1; j <= n; j ++)
                   if (map[i][j] == 1)
                   {
                      if (cur[i] != cur[j])
                         temp ++;
                      else
                          temp --;
                   }
               if (temp < 0)
               {
                  ans += temp;
                  f = 0;
                  continue;
               }
               cur[i] = 1 - cur[i];
           }
     }
}

int main()
{
    freopen("winner.in", "r", stdin);
    freopen("winner.out", "w", stdout);
    
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i ++)
    {
        scanf("%d", &inf[i]);
        cur[i] = inf[i];
    }
    memset(map, 0, sizeof map);
    ans = 0;
    for (i = 1; i <= m; i ++)
    {
        scanf("%d %d", &a, &b);
        if (inf[a] != inf[b])
           ans ++;
        map[a][b] = 1;
        map[a][0] ++;
        map[b][a] = 1;
        map[a][1] ++;
    }
    for (i = 1; i <= n; i ++)
        if (map[i][0] > 0)
           s ++;
    if (s <= 15)
       dfs(1, 0);
    else
        greedy();
    
    printf("%d\n", ans);
    
    return 0;
}
