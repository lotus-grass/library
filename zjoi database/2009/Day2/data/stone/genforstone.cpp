#include<stdio.h>
#include<stdlib.h>
#include<time.h>
const long T=10;
const long maxn=1000;
const long maxNum=1000000000;

long n;
long a[maxn+1];

long fl[maxn+1][maxn+1],fr[maxn+1][maxn+1];

long getn(){
    return (rand()<<15)+rand();
}

void makedata(){
    long i;
    n=rand()%(maxn-1)+2;
    for(i=1;i<=n;i++)a[i]=getn()%maxNum+1;
}

long get(long home,long away,long x){
    if(x==away)return 0;
    if(((x<home) && (x<away)) || ((x>home) && (x>away)))return x;
    if(home<away)return x+1;
    return x-1;
}

void makelose(){
    long i,j,k,l;
    for(i=1;i<=n;i++)fl[i][i]=fr[i][i]=a[i];
    for(l=1;l<n;l++){
	for(i=1;i+l<=n;i++){
            j=i+l;
	    fl[i][j]=get(fl[i][j-1],fr[i][j-1],a[j]);
	    fr[i][j]=get(fr[i+1][j],fl[i+1][j],a[i]);
	}
    }
    a[n]=fr[1][n-1];
    if(a[n]==0)n--;
}

main(){
    freopen("stone.in9","w",stdout);
    long i,j,k,l;
    srand(time(NULL));
    printf("%ld\n",T);
    for(i=1;i<=T;i++){
	makedata();
	if(rand()&1)makelose();
	printf("%ld\n",n);
	for(j=1;j<=n;j++)printf("%ld ",a[j]);
	printf("\n");
    }
    return 0;
}
