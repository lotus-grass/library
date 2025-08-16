#include<cstdio>

using namespace std;

inline long min(long a,long b)
{
    return a>b?a:b;
}

long i,n,a,b,c,d,u,v;
long lc[20000],lr[20000];

main()
{
    freopen("topguy.in","r",stdin);
    freopen("topguy.out","w",stdout);
    scanf("%d",&n);
    for (i=1;i<n;i++)
    {
        scanf("%d %d %d %d\n",&a,&b,&c,&d);
        lc[a]=c;lc[b]=d;lr[a]=d;lr[b]=c;
    }
    scanf("%d%d",&u,&v);
    printf("%d %d\n",0,min(lc[u],lr[v]));
}
