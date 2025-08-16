/*
  Name:     Numfill
  Copyright:Îâ×¿½Ü
  Author:   Îâ×¿½Ü
  Date: 12-04-07 10:09
  Description:¹¹Ôì
*/
#include<cstdio>
#define L 2000

using namespace std;

inline long A(long a)
{
    return (a>0?a:(-a));
}

long n,j,t,i,a[L];
bool b[L],bt;

main()
{
    freopen("Numfill.in","r",stdin);
    freopen("Numfill.out","w",stdout);
    scanf("%d",&n);
    if (n%4==1 || n%4==2) {printf("No\n"); return 0;}
    printf("Yes\n");
    for (i=2;i<=n;i++)
    {
        j=1;t=1;
        while (t<=n)
        {
            a[t]=j;
            j++;if (j==i) j++;
            t+=2;
        }
        j=n+1;t=2;
        while (t<=n)
        {
            a[t]=j;
            j--;if (j==i) j--;
            t+=2;
        }
        a[n+1]=a[1];
        bt=true;
        for (j=1;j<=n;j++) b[j]=false;
        for (j=1;j<=n;j++)
        {
            if (b[A(a[j+1]-a[j])]) {bt=false;break;}
            b[A(a[j+1]-a[j])]=true;
        }
        if (bt)
        {
            for (i=1;i<n;i++) printf("%d ",a[i]);
            printf("%d\n",a[n]);
            break;
        }
    }
}
