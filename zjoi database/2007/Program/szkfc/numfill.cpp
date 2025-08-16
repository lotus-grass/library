/*
  Prob: numfill 
  Author: K.F.Cat 
  Date: 12-04-07 08:48
  Description: Maybe it's right~ I love this kind of problems~
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 1010;

long n, s;
long i, j, k;
long ans[maxn], ok[maxn];

long check()
{
     long i;
     
     memset(ok, 0, sizeof ok);
     for (i = 2; i <= n; i ++)
         if (ok[abs(ans[i] - ans[i - 1])] == 0)
            ok[abs(ans[i] - ans[i - 1])] = 1;
         else
             return 0;
     if (ok[ans[n] - 1] == 0)
        return 1;
     else
         return 0;
}

int main()
{
    freopen("numfill.in", "r", stdin);
    freopen("numfill.out", "w", stdout);
    
    scanf("%d", &n);
    if (n % 4 == 1 || n % 4 == 2)
    {
       printf("No\n");
       return 0;
    }
    
    printf("Yes\n");
    for (i = 2; i <= n; i ++)
    {
        j = 1;
        k = n + 1;
        s = 0;
        while (j <= k)
        {
              s ++;
              ans[s] = j;
              if (j < k)
              {
                 s ++;
                 ans[s] = k;
              }
              j ++;
              if (j == i)
                 j ++;
              k --;
              if (k == i)
                 k --;
        }
        if (check() == 1)
        {
           for (j = 1; j < n; j ++)
               printf("%d ", ans[j]);
           printf("%d\n", ans[n]);
           return 0;
        }
    }
    
    return 0;
} 
