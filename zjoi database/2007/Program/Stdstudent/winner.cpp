#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int maxn=350;
const int ms=100000000;

int n,m,ts,best;

int c[maxn][maxn],f[maxn][maxn];
int origin[maxn];

void init(){
    int i,j,x,y;
    
    for (i=1;i<=n;++i) scanf("%d",&origin[i]);
    
    ts=n+1;
    
    for (i=0;i<=ts;++i) 
    for (j=0;j<=ts;++j)
        c[i][j]=f[i][j]=0;
    
    for (i=1;i<=m;++i){
        scanf("%d%d",&x,&y);
        if (origin[x]==origin[y]) c[x][y]=c[y][x]=1;
        else {
            if (origin[x]==0) c[x][y]=1;
            else c[y][x]=1;
        }    
    }    
    
    for (i=1;i<=n;++i)
        if (origin[i]==0) c[0][i]=1;
        else c[i][ts]=1;
}    

void work(){
    int i,j,valf,h,t,df;
    bool b[maxn];
    int q[maxn],pre[maxn];
    
    valf=0;
    do{
        for (i=0;i<=ts;++i) b[i]=false;
        b[0]=true;
        h=0;
        q[t=1]=0;
        while (h<t){
            i=q[++h];
            for (j=0;j<=ts;++j)
            if (!b[j] && f[i][j]<c[i][j]){
                q[++t]=j;
                b[j]=true;
                pre[j]=i;
            }    
        }    
        if (!b[ts]) break;
        
        i=ts;df=ms;
        while (i!=0){
            j=pre[i];
            if (c[j][i]-f[j][i]<df) df=c[j][i]-f[j][i];
            i=j;
        }    
        valf+=df;
        i=ts;
        while (i!=0){
            j=pre[i];
            f[j][i]+=df;
            f[i][j]=-f[j][i];
            i=j;
        }    
    }    
    while (true);
    
    best=valf;
}    

void print(){
    printf("%d\n",best);
}    

int main(){
    freopen("winner.in","r",stdin);
    freopen("winner.out","w",stdout);
    
    scanf("%d%d",&n,&m);
//    while (n!=0){
        init();
        work();
        print();
//        scanf("%d%d",&n,&m);
//    }    
    
    return 0;
}    
