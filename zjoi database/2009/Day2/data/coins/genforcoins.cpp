#include<stdio.h>
#include<stdlib.h>
#include<time.h>
const long maxn=100000;
const long maxT=1000;

long n;
long long T;

long bigrand(){
    return rand()*(1<<15)+rand();
}

long long getn(){
    return (long long)bigrand()*(1<<30)+bigrand();
}

main(){
    freopen("coins.in9","w",stdout);
    srand(time(NULL));
    long i;
    //T=getn()%(maxT+1);
    //n=rand()%maxn+1;
    T=getn();
    n=maxn/2+rand()%(maxn/2)+1;
    printf("%ld %I64d\n",n,T);
    for(i=1;i<=n;i++)printf("%ld ",(rand()&1)+1);
    printf("\n");
    return 0;
}
