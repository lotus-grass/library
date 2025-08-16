#include<stdio.h>
#include<memory.h>
#include<math.h>
const char inf[]="rec.in";
const char ouf[]="rec.out";
const long maxn=1000;

long n,m;
long map[maxn+1][maxn+1];

long H[maxn+1][maxn*2],S[maxn*2][maxn+1],f[maxn*2][maxn*2];
long list[maxn+1];

long ans;

void in(){
    long i,j,k;
    scanf("%ld%ld",&n,&m);
    for(i=1;i<=n;i++){
	for(j=1;j<=m;j++){
	    scanf("%ld",&map[i][j]);
	}
    }
}

void prepare(){
    long i,j,s,l,nowp,R;
    for(i=1;i<=n;i++){
	nowp=0;R=0;
	for(j=1;j<=m;j++){
	    l=nowp+nowp-j;
	    if((j<=R) && (j+H[i][l+l-1]-1<R))H[i][j+j-1]=H[i][l+l-1];
	    else{
		if(j<=R)s=H[i][l+l-1]<?(R-j+1);
		else s=0;
		for(;(j+s<=m) && (j-s>0) && (map[i][j+s]==map[i][j-s]);s++);
		H[i][j+j-1]=s;
		nowp=j;
		R=nowp+s-1;
	    }
	}
	nowp=0;R=0;
	for(j=1;j<m;j++){
	    l=nowp+nowp-j;
	    if((j<=R) && (j+H[i][l+l]-1<R))H[i][j+j]=H[i][l+l];
	    else{
	        if(j<=R)s=H[i][l+l]<?(R-j+1);
		else s=0;
		for(;(j-s>0) && (j+1+s<=m) && (map[i][j-s]==map[i][j+1+s]);s++);
		H[i][j+j]=s;
		nowp=j;
		R=nowp+s-1;
	    }
	}
    }
    for(j=1;j<=m;j++){
	nowp=0;R=0;
	for(i=1;i<=n;i++){
	    l=nowp+nowp-i;
	    if((i<=R) && (i+S[l+l-1][j]-1<R))S[i+i-1][j]=S[l+l-1][j];
	    else{
		if(i<=R)s=S[l+l-1][j]<?(R-i+1);
		else s=0;
		for(;(i+s<=n) && (i-s>0) && (map[i+s][j]==map[i-s][j]);s++);
		S[i+i-1][j]=s;
		nowp=i;
		R=nowp+s-1;
	    }
	}
	nowp=0;R=0;
	for(i=1;i<n;i++){
	    l=nowp+nowp-i;
	    if((i<=R) && (i+S[l+l][j]-1<R))S[i+i][j]=S[l+l][j];
	    else{
	        if(i<=R)s=S[l+l][j]<?(R-i+1);
		else s=0;
		for(;(i-s>0) && (i+1+s<=m) && (map[i-s][j]==map[i+1+s][j]);s++);
		S[i+i][j]=s;
		nowp=i;
		R=nowp+s-1;
	    }
	}
    }
}

void solve(){
    long i,j,s,t,now,maxL;
    for(i=1;i<n+n;i++){
	for(j=1;j<m+m;j++){
	    f[i][j]=maxn+1;
	}
    }
    for(i=1;i<n+n;i++){
	s=1;t=0;now=1;
	for(j=1;j<=m;j++){
	    list[++t]=j;
	    while((t>s) && (S[i][list[t]]<=S[i][list[t-1]]))list[--t]=list[t+1];
	    while((s<=t) && (S[i][list[s]]<j+1-now)){
		now++;
		if(list[s]<now)s++;
	    }
	    if(j<m)f[i][j+j]<?=j+1-now;
	    f[i][j+j-1]<?=j+1-now;
	}
	s=1;t=0;now=m;
	for(j=m;j>=1;j--){
	    list[++t]=j;
	    while((t>s) && (S[i][list[t]]<=S[i][list[t-1]]))list[--t]=list[t+1];
	    while((s<=t) && (S[i][list[s]]<now+1-j)){
		now--;
		if(list[s]>now)s++;
	    }
	    if(j>1)f[i][j+j-2]<?=now+1-j;
	    f[i][j+j-1]<?=now+1-j;
	}
    }
    for(j=1;j<m+m;j++){
	s=1;t=0;now=1;
	for(i=1;i<=n;i++){
	    list[++t]=i;
	    while((t>s) && (H[list[t]][j]<=H[list[t-1]][j]))list[--t]=list[t+1];
	    while((s<=t) && (H[list[s]][j]<i+1-now)){
		now++;
		if(list[s]<now)s++;
	    }
	    if(i<n)f[i+i][j]<?=i+1-now;
	    f[i+i-1][j]<?=i+1-now;
	}
	s=1;t=0;now=n;
	for(i=n;i>=1;i--){
	    list[++t]=i;
	    while((t>s) && (H[list[t]][j]<=H[list[t-1]][j]))list[--t]=list[t+1];
	    while((s<=t) && (H[list[s]][j]<now-i+1)){
		now--;
		if(list[s]>now)s++;
	    }
	    if(i>1)f[i+i-2][j]<?=now+1-i;
	    f[i+i-1][j]<?=now+1-i;
	}
    }
    ans=0;
    for(i=1;i<n+n;i++){
	for(j=1;j<m+m;j++){
	    if((i+j)&1)continue;
	    //printf("%ld %ld %ld\n",i,j,f[i][j]);
	    ans+=f[i][j];
        }
    }
}

void work(){
    prepare();
    solve();    
}

void out(){
    printf("%ld\n",ans);
}

main(){
    freopen(inf,"r",stdin);
    freopen(ouf,"w",stdout);
    in();
    work();
    out();
}
