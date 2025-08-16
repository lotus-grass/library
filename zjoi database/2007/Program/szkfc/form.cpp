/*
  Prob: form
  Author: K.F.Cat
  Date: 16-04-07 10:46
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 500001;
const long maxlongint = 2147483647;

long n, m;
long i, j;
long inf[maxn][3], num[maxn];
char str[30];
long temp = maxlongint, tail;

void work_gap()
{
     long i, j;
     long min = maxlongint;
     
     for (i = 1; i <= n; i ++)
     {
         j = i;
         while (inf[j][1] > 0)
         {
               min = min <? abs(inf[j][0] - inf[inf[j][1]][0]);
               j = inf[j][1];
         }
         if (i < n)
            min = min <? abs(inf[j][0] - inf[i + 1][0]);
     }
     printf("%d\n", min);
}

void sort(long l, long r)
{
     long i, j;
     long x, t;
     
     i = l;
     j = r;
     x = num[(i + j) >> 1];
     while (i < j)
     {
           while (num[i] < x)
                 i ++;
           while (num[j] > x)
                 j --;
           if (i <= j)
           {
              t = num[i];
              num[i] = num[j];
              num[j] = t;
              i ++;
              j --;
           }
     }
     if (i < r)
        sort(i, r);
     if (l < j)
        sort(l, j);
}

void work_sort()
{
     long i;
     
     if (temp > 0)
     {
        sort(1, tail);
        for (i = 2; i <= tail; i ++)
            temp = temp <? (num[i] - num[i - 1]);
     }
     printf("%d\n", temp);
}

void insert()
{
     long a, b;
     long help;
     
     scanf("%d %d", &a, &b);
     tail ++;
     inf[tail][0] = b;
     inf[tail][1] = 0;
     num[tail] = b;
     help = inf[a][2];
     inf[help][1] = tail;
     inf[a][2] = tail;
}

int main()
{
    freopen("form.in", "r", stdin);
    freopen("form.out", "w", stdout);
    
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i ++)
    {
        scanf("%d", &inf[i][0]);
        inf[i][1] = 0;
        inf[i][2] = i;
        num[i] = inf[i][0];
    }
    tail = n;
    
    for (i = 1; i <= m; i ++)
    {
        scanf("%s", &str);
        if (str[0] == 'I')
           insert();
        else
            if (str[4] == 'G')
               work_gap();
            else
                work_sort();
    }
    
    return 0;
}
