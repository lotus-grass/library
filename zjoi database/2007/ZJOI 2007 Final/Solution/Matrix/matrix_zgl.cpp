#include<stdio.h>
#include<string.h>
#define inpfilename "matrix.in"
#define outfilename "matrix.out"
#define maxn 210
int ncase,n;
int a[maxn][maxn];
int ty[maxn];
bool ny[maxn];
void read_data()
{
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++) scanf("%d",&a[i][j]);    
}
bool findpath(int u)
{
    int i;
    for (i=1;i<=n;i++) if (a[u][i]==1&&!ny[i])
    {
        ny[i]=true;
        if (ty[i]==0||findpath(ty[i]))
        {
            ty[i]=u;
            return true;
        }        
    }
    return false;
}
void process()
{
    memset(ty,0,sizeof(ty));
    int i;
    for (i=1;i<=n;i++)
    {
        memset(ny,0,sizeof(ny));
        if (!findpath(i))
        {
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
}
int main()
{
    freopen(inpfilename,"r",stdin);
    freopen(outfilename,"w",stdout);
    scanf("%d",&ncase);
    while (ncase)
    {
        ncase--;
        read_data();
        process();
    }
    read_data();
    return 0;
}
