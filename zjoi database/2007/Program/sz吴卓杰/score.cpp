/*
  Name:     score
  Copyright:Îâ×¿½Ü
  Author:   Îâ×¿½Ü
  Date: 12-04-07 10:44
  Description:DP
*/
#include<cstdio>
#include<cstring>
#define L 101

using namespace std;

long zb[5][L],down[5][L],tr[5];

inline long max(long a,long b)
{
    return a>b?a:b;
}
long sear(long a,long b,long c,long d,long r);

long dp(long a,long b,long c,long d)
{
    if ((a|b|c|d)==0) return 0;
    long tem=sear(a,b,c,d,-1);
    if (tem<0)
    {
            long ma=0;
            if (a==b&&b==c&&a!=0&&d<=a) ma=max(ma,a*3+dp(down[1][a],down[2][b],down[3][c],d));
            if (a==b&&b==d&&a!=0&&c<=a) ma=max(ma,a*3+dp(down[1][a],down[2][b],c,down[4][d]));
            if (a==c&&d==c&&a!=0&&b<=a) ma=max(ma,a*3+dp(down[1][a],b,down[3][c],down[4][d]));
            if (d==b&&b==c&&b!=0&&a<=b) ma=max(ma,b*3+dp(a,down[2][b],down[3][c],down[4][d]));
            if (a==b&&b==c&&c==d)
                ma=max(ma,a*4+dp(down[1][a],down[2][b],down[3][c],down[4][d]));
            long s,i;
            if (a>=b && a>=c && a>=d)
            {
                s=a;
                for (i=1;i<=4 && i<a;i++)
                    if (zb[1][a-i])
                    {
                        s+=a-i;
                        if (i>1)ma=max(ma,s+dp(down[1][a-i],b,c,d));
                    }
                s=0;
                ma=max(ma,dp(down[1][a],b,c,d));
            }
            else if (b>=a && b>=c && b>=d)
            {
                s=b;
                for (i=1;i<=4 && i<b;i++)
                    if (zb[2][b-i])
                    {
                        s+=b-i;
                        if (i>1)ma=max(ma,s+dp(a,down[2][b-i],c,d));
                    }
                s=0;
                ma=max(ma,dp(a,down[2][b],c,d));
            }
            else if (c>=a && c>=b && c>=d)
            {
                s=c;
                for (i=1;i<=4 && i<c;i++)
                    if (zb[3][c-i])
                    {
                        s+=c-i;
                        if (i>1)ma=max(ma,s+dp(a,b,down[3][c-i],d));
                    }
                s=0;
                ma=max(ma,dp(a,b,down[3][c],d));
            }
            else
            {
                s=d;
                for (i=1;i<=4 && i<d;i++)
                    if (zb[4][d-i])
                    {
                        s+=d-i;
                        if (i>1)ma=max(ma,s+dp(a,b,c,down[4][d-i]));
                    }
                s=0;
                ma=max(ma,dp(a,b,c,down[4][d]));
            }
            return sear(a,b,c,d,ma);
        }
    else return tem;
}

long n,i,tem,ma,j,a,b,c,d;
char ch;

main()
{
    freopen("score.in","r",stdin);
    freopen("score.out","w",stdout);
    scanf("%d",&n);
    for (i=1;i<=n;i++)
    {
        scanf("%d%c",&a,&ch);
        switch (ch)
        {
            case 'y':tem=1;break;
            case 'r':tem=2;break;
            case 'g':tem=3;break;
            case 'b':tem=4;break;
        }
        zb[tem][a]=true;
    }
    zb[1][0]=zb[2][0]=zb[3][0]=zb[4][0]=true;
    for (i=1;i<=4;i++)
    {
        ma=0;
        for (j=0;j<=100;j++)
            if (zb[i][j])
            {
                down[i][j]=ma;
                ma=j;
            }
        tr[i]=ma;
    }
    printf("%d\n",dp(tr[1],tr[2],tr[3],tr[4]));
}

const long hashlen=300001;
long hash[hashlen],v[hashlen];

long sear(long a,long b,long c,long d,long r)
{
    long tem=(((a*101+b)*101+c)*101+d);
    long u=tem%hashlen;
    while (hash[u]!=0 && hash[u]!=tem) u=(u+1)%hashlen;
    if (hash[u]==0) {hash[u]=tem;v[u]=-1;}
    if (r>=0) v[u]=r;
    return v[u];
}
