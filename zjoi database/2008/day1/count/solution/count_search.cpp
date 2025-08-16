//brute_force_search
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

void dfs(int,int);
int calc1(int,int);
int calc2(int,int);
int w[30010],pre[30010],dep[30010],n,m,x,y;
vector <int> edge[30010];
char str[100];

int main(){
    freopen("count.in","r",stdin);
    freopen("count.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) edge[i].clear();
    for (int i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    for (int i=1;i<=n;i++) scanf("%d",&w[i]);
    dep[0]=0;
    w[0]=-100000;
    dfs(1,0);
    scanf("%d",&m);
    for (int i=0;i<m;i++){
        scanf("%s%d%d",&str,&x,&y);
        if (str[0]=='C') w[x]=y;
        if (str[1]=='M') printf("%d\n",calc1(x,y));
        if (str[1]=='S') printf("%d\n",calc2(x,y));
    }
    return 0;
}

void dfs(int x,int fa){
    dep[x]=dep[fa]+1;
    pre[x]=fa;
    for (int i=0;i<edge[x].size();i++)
        if (edge[x][i]!=fa)
            dfs(edge[x][i],x);
}

int calc1(int x,int y){
    int ret=w[x];
    if (w[y]>w[x]) ret=w[y];
    while (x!=y){
        if (dep[x]>dep[y]){
            x=pre[x];
            if (w[x]>ret) ret=w[x];
        }
        else{
            y=pre[y];
            if (w[y]>ret) ret=w[y];
        }
    }
    return ret;
}

int calc2(int x,int y){
    int ret=w[x];
    ret+=w[y];
    while (x!=y)
        if (dep[x]>dep[y]) ret+=w[x=pre[x]];
        else ret+=w[y=pre[y]];
    return ret-w[x];
}
