/*
  Prob: score
  Author: K.F.Cat
  Date: 12-04-07 10:58
  Description: ¿ªÊ¼Æ­µã 
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 400;

long n;
long i, j;
long val[maxn];
char code[maxn], color;
long s, ans, num;

int main()
{
    freopen("score.in", "r", stdin);
    freopen("score.out", "w", stdout);
    
    scanf("%d", &n);
    for (i = 1; i <= n; i ++)
        scanf("%d%c", &val[i], &code[i]);
    val[n + 1] = -1;
    
    ans = 0;
    color = code[1];    
    s = 1;
    for (i = 2; i <= n; i ++)
        if (color == code[i])
           s ++;
        else
        {
            if (s >= 3)
               for (j = i - 1; j >= i - s; j --)
               {
                   ans += val[j];
                   val[j] = 0;
               }
            color = code[i];
            s = 1;
        }
        
    for (i = 1; i < n; i ++)
        for (j = i + 1; j <= n; j ++)
            if (val[i] < val[j])
            {
               val[0] = val[i];
               val[i] = val[j];
               val[j] = val[0];
            }
    num = val[1];    
    s = 1;
    for (i = 2; i <= n + 1; i ++)
        if (num == val[i])
           s ++;
        else
        {
            if (s >= 3)
               for (j = i - 1; j >= i - s; j --)
               {
                   ans += val[j];
                   val[j] = 0;
               }
            num = val[i];
            s = 1;
        }
    printf("%d\n", ans);
    
    return 0;
}
