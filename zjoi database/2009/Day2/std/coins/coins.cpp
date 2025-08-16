#include<stdio.h>
#include<memory.h>
const char inf[]="coins.in";
const char ouf[]="coins.out";
const long maxn=100000;

long n;
long long T;

long pre[maxn+1],state[maxn+10];

void in(){
    long i;
    scanf("%ld%I64d",&n,&T);
    for(i=1;i<=n;i++){
        scanf("%ld",state+i);
        state[i]--;
    }
}

void work(){
    long i,l,r,k;
    long long p;
    for(p=1;p<=(T>>1);p<<=1){
	if(p&(T>>1)){
	    memcpy(pre,state,sizeof(long)*(n+1));
	    for(i=1;i<=n;i++){
	        k=p%n;
		l=(i-k+n-1)%n+1;
		r=(i+k-1)%n+1;
		state[i]=pre[l]^pre[r];
	    }
	}
    }
    state[0]=state[n];
    state[n+1]=state[1];
}

void out(){
    long i;
    if(T&1)for(i=1;i<=n;i++)printf("0 %ld ",(state[i]^state[i+1])+1);
    else for(i=1;i<=n;i++)printf("%ld 0 ",state[i]+1);
    printf("\n");
}

main(){
    freopen(inf,"r",stdin);
    freopen(ouf,"w",stdout);
    in();
    work();
    out();
    return 0;
}
