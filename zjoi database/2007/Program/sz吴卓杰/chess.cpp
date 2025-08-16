/*
  Name:     chess
  Copyright:Îâ×¿½Ü
  Author:   Îâ×¿½Ü
  Date: 16-04-07 08:18
  Description:dp
*/
#include<cstdio>
#define L 5000

using namespace std;

long i,j,n,m,tem,temp,bma,ma;
long map[L][L],h[L][L],z[L][L],y[L][L];

inline long min(long a,long b)
{
    return a<b?a:b;
}

main()
{
    freopen("chess.in","r",stdin);
    freopen("chess.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            scanf("%d",&map[i][j]);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            if (i>1 && map[i-1][j]!=map[i][j]) h[i][j]=h[i-1][j];else h[i][j]=i;
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            if (j>1 && map[i][j-1]!=map[i][j])
            {
                tem=j-1;temp=j;
                while (tem!=temp && h[i][tem]<=h[i][j])
                {
                    temp=tem;
                    tem=z[i][tem];
                }
                z[i][j]=tem;
            }
            else z[i][j]=j;
    for (i=1;i<=n;i++)
        for (j=m;j;j--)
            if (j<m && map[i][j+1]!=map[i][j])
            {
                tem=j+1;temp=j;
                while (tem!=temp && h[i][tem]<=h[i][j])
                {
                    temp=tem;
                    tem=y[i][tem];
                }
                y[i][j]=tem;
            }
            else y[i][j]=j;
    bma=ma=0;
    for (i=1;i<=n;i++)
        for (j=i;j<=m;j++)
        {
            if (h[i][z[i][j]]<=h[i][j]) z[i][j]--;
            if (h[i][y[i][j]]<=h[i][j]) y[i][j]++;
            tem=min(y[i][j]-z[i][j]-1,i-h[i][j]+1);
            if (tem>bma) bma=tem;
            if ((y[i][j]-z[i][j]-1)*(i-h[i][j]+1)>ma) ma=(y[i][j]-z[i][j]-1)*(i-h[i][j]+1);
        }
    printf("%d\n%d\n",bma*bma,ma);
}
