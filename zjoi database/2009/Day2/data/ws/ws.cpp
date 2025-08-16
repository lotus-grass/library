#include<stdio.h>
const char inf[]="ws.in9";
const char ouf[]="ws.out9";
const long fx[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
const long maxn=100;
const long maxNode=maxn*maxn+2;
const long maxE=maxn*maxn*5;
const long INF=1<<30;
struct ljb{
    long no,flow,limit,ff,next;     
};

long n,m;
long map[maxn+1][maxn+1];

long head[maxNode+1],gg[maxNode+1],st,en,last;
struct ljb mem[maxE*2+10];

long list[maxNode+1],dist[maxNode+1],s,t;

long ans;

void in(){
    long i,j;
    scanf("%ld%ld",&n,&m);
    for(i=1;i<=n;i++){
	for(j=1;j<=m;j++){
	    scanf("%ld",&map[i][j]);
	}
    }
}

void insert(long a,long b,long limit){
    mem[++last].no=b;mem[last].limit=limit;
    mem[last].flow=0;mem[last].next=head[a];
    head[a]=last;

    mem[++last].no=a;mem[last].limit=0;
    mem[last].flow=0;mem[last].next=head[b];
    head[b]=last;

    mem[last].ff=last-1;
    mem[last-1].ff=last;
}

void buildgraph(){
    long i,j,k,dx,dy;
    st=0;en=n*m+1;last=0;
    for(i=1;i<=n;i++){
	for(j=1;j<=m;j++){
	    for(k=0;k<=3;k++){
		dx=i+fx[k][0];
		dy=j+fx[k][1];
		if((dx>0) && (dx<=n) && (dy>0) && (dy<=m)){
		    insert((i-1)*m+j,(dx-1)*m+dy,1);
		}
	    }
	    if(map[i][j]==1)insert(st,(i-1)*m+j,INF);
	    else if(map[i][j]==2)insert((i-1)*m+j,en,INF);
	}
    }
}

long bfs(){
    long i,u,v;
    for(i=st;i<=en;i++)dist[i]=INF;
    dist[st]=0;
    list[t=1]=st;s=0;
    while(s<t){
	u=list[++s];
	for(i=head[u];i;i=mem[i].next){
	    v=mem[i].no;
	    if((dist[v]>dist[u]+1) && (mem[i].flow<mem[i].limit)){
		dist[list[++t]=v]=dist[u]+1;
	    }
	}
    }
    return (dist[en]<INF);
}

long dfs(long x,long min){
    long i,v,l,flow=0;
    if(x==en)return min;
    for(;gg[x];gg[x]=mem[gg[x]].next){
	i=gg[x];
	v=mem[i].no;
	if((dist[v]==dist[x]+1) && (mem[i].flow<mem[i].limit)){
	    l=dfs(v,(mem[i].limit-mem[i].flow)<?(min-flow));
	    mem[i].flow+=l;
	    mem[mem[i].ff].flow-=l;
	    flow+=l;
	}
	if(min==flow)break;
    }
    return flow;
}

void dinic(){
    long i;
    ans=0;
    while(bfs()){
	for(i=st;i<=en;i++)gg[i]=head[i];
	ans+=dfs(st,INF);
    }
}

void work(){
    buildgraph();
    dinic();
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
    return 0;
}
