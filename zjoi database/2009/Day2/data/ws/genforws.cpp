#include<stdio.h>
#include<stdlib.h>
#include<time.h>
const long n=100;
const long m=100;

main(){
    freopen("ws.in9","w",stdout);
    srand(time(NULL));
    //n=rand()%3+1;m=rand()%3+1;
    long i,j,k;
    printf("%ld %ld\n",n,m);
    for(i=1;i<=n;i++){
	for(j=1;j<=m;j++){
	    printf("%ld ",rand()%3);
	}
	printf("\n");
    }
    return 0;
}
