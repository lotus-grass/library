/*
  Name:     form
  Copyright:Îâ×¿½Ü
  Author:   Îâ×¿½Ü
  Date: 16-04-07 08:58
  Description:Ä£Äâ
*/
#include<cstdio>
#include<cstdlib>
#define L 1000000
#define M 0x3ffffff

using namespace std;

long n,m,i,tem,ti,tk,len,r;
char str[100];
long z[L],y[L],num[L],c[L],en[L],zt[L],ans[L];
struct no{long num,t;}dl[L];

inline long A(long a)
{
    return a>0?a:-a;
}

inline long min(long a,long b)
{
    return a<b?a:b;
}

int cmp(const void *a,const void *b)
{
    if (((no *)a)->num<((no *)b)->num) return -1;
    else return 1;
}

main()
{
    freopen("form.in","r",stdin);
    freopen("form.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
    {
        scanf("%d",&num[i]);
        en[i]=num[i];
        dl[++len].num=num[i];
        dl[len].t=0;
    }
    r=M;
    qsort(dl+1,len,sizeof(no),cmp);
    for (i=1;i<len;i++) if (r>dl[i+1].num-dl[i].num) r=dl[i+1].num-dl[i].num;
    c[0]=r;
    for (i=1;i<=m;i++)
    {
        scanf("%s",str);
        c[i]=M;
        if (str[4]=='R')
        {
            scanf("%d %d",&ti,&tk);
            zt[i]=1;
            dl[++len].num=tk;
            dl[len].t=i;
            r=min(r,A(tk-en[ti]));
            if (ti<n) r=min(r,A(tk-num[ti+1]));
            en[ti]=tk;
        }
        else if (str[4]=='G')
        {
            zt[i]=2;
            ans[i]=r;
        }
        else zt[i]=3;
    }
    qsort(dl+1,len,sizeof(no),cmp);
    z[1]=0;y[len]=0;
    for (i=2;i<=len;i++)
    {
        tem=i-1;
        while (tem && dl[tem].t>dl[i].t) tem=z[tem];
        z[i]=tem;
    }
    for (i=len-1;i;i--)
    {
        tem=i+1;
        while (tem && dl[tem].t>dl[i].t) tem=y[tem];
        y[i]=tem;
    }
    for (i=1;i<=len;i++)
    if (dl[i].t)
    {
        if (z[i]) c[dl[i].t]=min(c[dl[i].t],dl[i].num-dl[z[i]].num);
        if (y[i]) c[dl[i].t]=min(c[dl[i].t],dl[y[i]].num-dl[i].num);
    }
    for (i=1;i<=m;i++)
    {
        if (c[i-1]<c[i]) c[i]=c[i-1];
        if (zt[i]==2) printf("%d\n",ans[i]);
        else if (zt[i]==3) printf("%d\n",c[i]);
    }
}
