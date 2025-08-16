//Care about stack room!!!
#include<stdio.h>
#include<string.h>
#define inpfilename "synch.5.in"
#define outfilename "synch.out"
#define maxn 1000010
int n,root,nedge,cl,op;
int first[maxn],node[2*maxn],cost[2*maxn],next[2*maxn];
int queue[maxn],father[maxn],max[maxn];
void addedge(int u,int v,int w)
{
    nedge++;
    node[nedge]=v;
    cost[nedge]=w;
    next[nedge]=first[u];
    first[u]=nedge;
}  
void read_data()
{
    int i,u,v,w;
    scanf("%d%d",&n,&root);
    for (i=1;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
        addedge(v,u,w);
    }    
}      
void bfs()
{
    int i,u,v;
    cl=0;op=1;queue[1]=root;
    while (cl<op)
    {
        cl++;
        u=queue[cl];
        i=first[u];
        while (i>0)
        {
            v=node[i];
            if (father[u]!=v)
            {
                father[v]=u;
                op++;
                queue[op]=v;
            }    
            i=next[i];
        }    
    }    
}   
void getans()
{
    int j,i,u,v,tmp;
    __int64 ans=0;
    for (j=n;j>0;j--)
    {
        u=queue[j];
        i=first[u];
        while (i>0)
        {
            v=node[i];
            if (father[v]==u)
            {
                tmp=max[v]+cost[i];
                if (max[u]<tmp) max[u]=tmp;
            }    
            i=next[i];
        }    
        i=first[u];
        while (i>0)
        {
            v=node[i];
            if (father[v]==u)
            {
                tmp=max[v]+cost[i];
                ans+=(__int64)max[u]-tmp;
            }    
            i=next[i];
        }    
    }    
    printf("%I64d\n",ans);
}     
int main()
{
   freopen(inpfilename,"r",stdin);
   freopen(outfilename,"w",stdout);
    read_data();
    bfs();
    getans();
    return 0; 
}     
