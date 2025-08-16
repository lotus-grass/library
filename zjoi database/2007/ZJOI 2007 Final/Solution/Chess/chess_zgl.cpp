#include<stdio.h>
#define inpfilename "chess.in"
#define outfilename "chess.out"
#define maxn 2005
int n,m,ans1,ans2;
short a[maxn][maxn];
short lef[maxn][maxn],rig[maxn][maxn],up[maxn][maxn];
short opt[maxn][maxn];
void read_data()
{
    int i,j;
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
       for (j=1;j<=m;j++) scanf("%d",&a[i][j]);
}
void prepare()
{
    int i,j;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++) 
            if (i>1&&a[i][j]^a[i-1][j]==1) up[i][j]=up[i-1][j]+1;
        for (j=2;j<=m;j++) 
            if (a[i][j]^a[i][j-1]==1) lef[i][j]=lef[i][j-1]+1;
        for (j=m-1;j>0;j--) 
            if (a[i][j]^a[i][j+1]==1) rig[i][j]=rig[i][j+1]+1;
    }
}
short getmin(short x,short y,short z)
{
    if (x<y) return (x<z)?x:z; else return (y<z)?y:z;
}
void getans1()
{
    int i,j;
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        {
            if (i==1||j==1) continue;
            if (a[i][j]!=a[i-1][j-1]) continue;
            opt[i][j]=getmin(opt[i-1][j-1]+1,up[i][j],lef[i][j]);
            if (ans1<opt[i][j]) ans1=opt[i][j];
        }
    ans1++;
}
void getans2()
{
    int i,j;
    for (i=1;i<=n;i++) 
    {
        for (j=1;j<=m;j++)
        {
            if (i>1&&a[i][j]^a[i-1][j]==1) 
            {
                lef[i][j]=getmin(lef[i][j],lef[i-1][j],maxn+1);
                rig[i][j]=getmin(rig[i][j],rig[i-1][j],maxn+1);                
            }
            int tmp=(lef[i][j]+rig[i][j]+1)*(up[i][j]+1);
            if (ans2<tmp) ans2=tmp;
        }
    }
}
int main()
{
    freopen(inpfilename,"r",stdin);
    freopen(outfilename,"w",stdout);
    read_data();
    prepare();
    getans1();
    getans2();
    printf("%d %d\n",ans1*ans1,ans2);
    return 0;
}
