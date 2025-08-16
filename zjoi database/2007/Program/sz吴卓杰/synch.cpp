/*
  Name:     synch
  Copyright:Îâ×¿½Ü
  Author:   Îâ×¿½Ü
  Date: 16-04-07 09:43
  Description:DFS
*/
#include<cstdio>
#define L 2000000

using namespace std;

long n,s,i,t;
long long q;
long qd[L],end[L],len[L],ki[L],z[L],fa[L],gs[L];
long long qz[L],tim[L];
struct {long a,b,t;}tdx[L],dx[L];
bool ct,bt[L];

main()
{
    freopen("synch.in","r",stdin);
    freopen("synch.out","w",stdout);
    scanf("%d%d",&n,&s);
    for (i=1;i<n;i++)
    {
        scanf("%d%d%d",&tdx[i*2-1].a,&tdx[i*2-1].b,&tdx[i*2-1].t);
        tdx[i*2].a=tdx[i*2-1].b;
        tdx[i*2].b=tdx[i*2-1].a;
        tdx[i*2].t=tdx[i*2-1].t;
    }
    for (i=1;i<=n*2-2;i++) len[tdx[i].a]++;
    qd[0]=1;
    for (i=1;i<=n;i++) end[i]=(qd[i]=qd[i-1]+len[i-1])-1;
    for (i=1;i<=n*2-2;i++)
    {
        dx[++end[tdx[i].a]].b=tdx[i].b;
        dx[end[tdx[i].a]].t=tdx[i].t;
    }
//    for (i=1;i<=n*2-2;i++) printf("%d %d %d\n",dx[i].a,dx[i].b,dx[i].t);
    t=1;z[1]=s;ki[1]=qd[s];bt[1]=true;
    while (t)
    {
        ct=false;
        for (;ki[t]<=end[z[t]];ki[t]++)
            if (fa[z[t]]!=dx[ki[t]].b)
            {
                if (bt[t])
                {
                    fa[dx[ki[t]].b]=z[t];
                    z[t+1]=dx[ki[t]].b;
                    bt[t+1]=true;
                    ki[t+1]=qd[dx[ki[t]].b];
                    qz[t+1]=0;
                    tim[dx[ki[t]].b]=0;
                    gs[t+1]=0;
                    ct=true;
                    bt[t]=false;
                    break;
                }
                qz[t]+=tim[dx[ki[t]].b]+dx[ki[t]].t;
                if (tim[z[t]]<tim[dx[ki[t]].b]+dx[ki[t]].t)
                    tim[z[t]]=tim[dx[ki[t]].b]+dx[ki[t]].t;
                gs[t]++;
                bt[t]=true;
            }
        if (ct) {t++;continue;}
        else
        {
            q+=gs[t]*tim[z[t]]-qz[t];
            t--;
        }
    }
    printf("%I64d\n",q);
}
