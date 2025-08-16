#include<stdio.h>
#include<stdlib.h>
#include<time.h>
const long maxN=2;
const long n=1000;
const long m=1000;
const long maxL=n<?m;
const long cTime=1000;

long map[n+1][m+1];

main(){
    freopen("rec.in9","w",stdout); 
    srand(time(NULL));
    long i,j,k,l,sx,sy;
    printf("%ld %ld\n",n,m);    
    for(i=1;i<=n;i++){
	for(j=1;j<=m;j++){
	    map[i][j]=rand()%maxN+1;
	}
    }
    for(i=1;i<=cTime;i++){
	l=rand()%maxL+1;
	sx=rand()%(n+1-l)+1;
	sy=rand()%(m+1-l)+1;
	for(j=1;j<=(l+1)/2;j++){
	    for(k=1;k<=(l+1)/2;k++){
		map[sx+j-1][sy+j-1]=rand()%maxN+1;
	    }
	}
	for(j=1;j<=(l+1)/2;j++){
	    for(k=1;k<=l/2;k++){
		map[sx+l-k][sy+j-1]=map[sx+k-1][sy+j-1];
	    }
	}
	for(j=1;j<=l;j++){
	    for(k=1;k<=l/2;k++){
		map[sx+j-1][sy+l-k]=map[sx+j-1][sy+k-1];
	    }
	}
    }
    for(i=1;i<=n;i++){
	for(j=1;j<=m;j++){
	    printf("%ld ",map[i][j]);
	}
	printf("\n");
    }
    return 0;
}
