#include<cstdio>

using namespace std;

long n,m,i,a,s;

main()
{
    freopen("winner.in","r",stdin);
    freopen("winner.out","w",stdout);
    scanf("%d %d",&n,&m);
    for (i=1;i<=n;i++) {scanf("%d",&a); s+=a;}
    if (s*2>n) printf("%d\n",n-s);else printf("%d\n",s);
}
