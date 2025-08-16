#include<stdio.h>
const char inf[]="stone.in9";
const char ouf[]="stone.out9";
const char *ansstr[]={"0","1"};
const long maxn=1000;

long T,n;
long a[maxn+1];

long fl[maxn+1][maxn+1],fr[maxn+1][maxn+1];

long ans;

void in(){
    long i;
    scanf("%ld",&n);
    for(i=1;i<=n;i++)scanf("%ld",a+i);
}

long get(long home,long away,long x){
    if(x==away)return 0;
    if(((x<home) && (x<away)) || ((x>home) && (x>away)))return x;
    if(home<away)return x+1;
    return x-1;
}

void work(){
    long i,j,k,l;
    for(i=1;i<=n;i++)fl[i][i]=fr[i][i]=a[i];
    for(l=1;l<n;l++){
	for(i=1;i+l<=n;i++){
            j=i+l;
	    fl[i][j]=get(fl[i][j-1],fr[i][j-1],a[j]);
	    fr[i][j]=get(fr[i+1][j],fl[i+1][j],a[i]);
	}
    }
    if(n==1)ans=1;
    else ans=1-(fr[1][n-1]==a[n]);
}

void out(){
    printf("%s\n",ansstr[ans]);
}

main(){
    freopen(inf,"r",stdin);
    freopen(ouf,"w",stdout);
    for(scanf("%ld",&T);T;T--){
        in();
        work();
        out();
    }
    return 0;
}
