//Operation:
//INSERT i k
//MIN-GAP
//MIN-SORT-GAP 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define inpfilename "form.in"
#define outfilename "form.out"
#define maxn 1000010 
struct tnode 
{
    int key;
    int hvalue;
    int lchild,rchild;    
};
struct tbst 
{
    private: 
        int root,cnt,min; 
        tnode data[maxn];
        int merge(int p,int q);
        void insert(int &node,int newkey);
    public:
        void setnull(); 
        void insert(int newkey);
        void remove(int &node,int oldkey);
        int getmin();
};    
struct theap
{
    private:
        int nheap;
        int key[maxn],lnk[maxn],pos[maxn];
        void swap(int i,int j); 
        void upsift(int p);
        void downsift(int p);
    public:
        void setnull(); 
        void insert(int newkey);
        void modify(int newkey,int p);
        int getmin();
};     
int n,m;
int head[maxn],tail[maxn];
tbst bst; 
theap heap;
void tbst::setnull()
{
    cnt=root=0;min=2000000000;
    memset(data,0,sizeof(data));
}    
void tbst::insert(int &node,int newkey)
{
    if (node==0)
    {
        cnt++;node=cnt;
        data[node].key=newkey;
        data[node].hvalue=rand()<<13+rand();
        data[node].lchild=data[node].rchild=0;
        return;
    }
    int temp=abs(newkey-data[node].key);
    if (min>temp) min=temp;
    if (newkey<data[node].key)
    {
        insert(data[node].lchild,newkey);
        temp=data[node].lchild;
        if (data[temp].hvalue<data[node].hvalue)
        {
            data[node].lchild=data[temp].rchild;
            data[temp].rchild=node;
            node=temp;
        }        
    }
    else
    {
        insert(data[node].rchild,newkey);
        temp=data[node].rchild;
        if (data[temp].hvalue<data[node].hvalue)
        {
            data[node].rchild=data[temp].lchild;
            data[temp].lchild=node;
            node=temp;
        }        
    }        
}
void tbst::insert(int newkey)
{
    insert(root,newkey);
}    
int tbst::merge(int p,int q)
{
    if (q==0) return p; else
    if (p==0) return q; else
    if (data[p].hvalue<data[q].hvalue)
    {
        data[p].rchild=merge(data[p].rchild,q);
        return p;
    }
    else
    {
        data[q].lchild=merge(p,data[q].lchild);
        return q;
    }        
}
int tbst::getmin()
{
    return min;
}    
void theap::setnull()
{
    nheap=0;
    memset(pos,0,sizeof(pos));
}    
void theap::swap(int i,int j)
{
    int t;
    t=key[i];key[i]=key[j];key[j]=t;
    t=lnk[i];lnk[i]=lnk[j];lnk[j]=t;
    pos[lnk[i]]=i;
    pos[lnk[j]]=j;
}       
void theap::upsift(int p)
{
    int i=p,j;
    while (i>1)
    {
        j=i/2;
        if (key[i]<key[j])
        {
            swap(i,j);
            i=j;
        }
        else
            break;    
    }    
}    
void theap::downsift(int p)
{
    int i=p,j;
    while (i<=nheap/2)
    {
        j=i+i;
        if (j<nheap&&key[j+1]<key[j]) j++;
        if (key[i]>key[j])
        {
            swap(i,j);
            i=j;
        }
        else
            break;
    }    
}
void theap::insert(int newkey)    
{
    nheap++;
    key[nheap]=newkey;
    lnk[nheap]=nheap;
    pos[nheap]=nheap;
    upsift(nheap);
}    
void theap::modify(int newkey,int p)
{
    key[pos[p]]=newkey;
    upsift(pos[p]);
    downsift(pos[p]);    
}    
int theap::getmin()
{
    return key[1]; 
}    
int main()
{
    scanf("%d%d",&n,&m);
    bst.setnull();
    heap.setnull();
    int i;
    for (i=1;i<=n;i++)
    {
        scanf("%d",&head[i]);
        tail[i]=head[i];
        bst.insert(head[i]);
        if (i>1) heap.insert(abs(head[i]-head[i-1]));
    }    
    while (m>0) 
    {
        m--;
        char oper[100];
        scanf("%s",&oper);
        if (oper[4]=='R') //INSERT 
        {
            int i,x,p;
            scanf("%d%d",&i,&x);
            bst.insert(x);
            if (i<n) heap.modify(abs(x-head[i+1]),i);
            heap.insert(abs(x-tail[i]));
            tail[i]=x;
        }
        else
        if (oper[4]=='G') //MIN-GAP 
        {
            printf("%d\n",heap.getmin());
        }
        else
        if (oper[4]=='S') //MIN-SORT-GAP     
        {
            printf("%d\n",bst.getmin());
        }    
    }    
    return 0; 
}     
