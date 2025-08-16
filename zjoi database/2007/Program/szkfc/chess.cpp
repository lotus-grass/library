/*
  Prob: chess
  Author: K.F.Cat
  Date: 16-04-07 09:47
  Description: À¢π„∏Ê≈∆... 
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 2001;

long n, m;
long i, j;
long inf[maxn][maxn], max[maxn][maxn], l[maxn], r[maxn];
long a, b;

int main()
{
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    
    scanf("%d %d", &n, &m);
    memset(max, 0, sizeof max);
    for (i = 1; i <= n; i ++)
        for (j = 1; j <= m; j ++)
        {
            scanf("%d", &inf[i][j]);
            if (i > 1 && inf[i][j] != inf[i - 1][j])
               max[i][j] = max[i - 1][j] + 1;
            else
                max[i][j] = 1;
        }
        
    a = 0;
    b = 0;
    for (i = 1; i <= n; i ++)
    {
        l[1] = 0;
        for (j = 2; j <= m; j ++)
        {
            l[j] = j - 1;
            while (l[j] > 0 && max[i][j] <= max[i][l[j]] && (inf[i][j] xor inf[i][l[j]]) == ((j - l[j]) & 1))
                  l[j] = l[l[j]];
        }
        r[m] = m + 1;
        for (j = m - 1; j > 0; j --)
        {
            r[j] = j + 1;
            while (r[j] <= m && max[i][j] <= max[i][r[j]] && (inf[i][j] xor inf[i][r[j]]) == ((r[j] - j) & 1))
                  r[j] = r[r[j]];
            b = b >? ((r[j] - l[j] - 1) * max[i][j]);
            if (max[i][j] <= r[j] - l[j] - 1)
               a = a >? max[i][j];
        }
    }
    printf("%d %d\n", a * a, b);
    
    return 0;
}
