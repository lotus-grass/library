/*
  Name:     matrix
  Copyright:Îâ×¿½Ü
  Author:   Îâ×¿½Ü
  Date: 16-04-07 10:40
  Description:¶þ·ÖÍ¼Æ¥Åä
*/
#include<cstdio>
#define L 1000

using namespace std;

long t,i,j,n,s;
long yp[L],zp[L];
bool map[L][L],zbj[L],ybj[L];

bool dfs(long);

main()
{
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    for(scanf("%d",&t);t;--t)
    {
        scanf("%d",&n);
        s=0;
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
                scanf("%d",&map[i][j]);
        for (i=1;i<=n;i++) yp[i]=zp[i]=0;
        for (i=1;i<=n;i++)
            if (zp[i]==0)
            {
                for (j=1;j<=n;j++) zbj[j]=ybj[j]=true;
                dfs(i);
            }
        for (i=1;i<=n;i++) if (zp[i]) s++;
        if (s==n) printf("Yes\n");
        else printf("No\n");
    }
}

bool dfs(long a)
{
    if (zbj[a]) zbj[a]=false;
    else return false;
    for (long i=1;i<=n;i++)
        if (map[a][i])
            if (yp[i]==0)
            {
                yp[i]=a;
                zp[a]=i;
                return true;
            }
            else if (dfs(yp[i]))
            {
                yp[i]=a;
                zp[a]=i;
                return true;
            }
    return false;
}
                
