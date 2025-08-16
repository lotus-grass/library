//Author:Fluorine
#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;

int calc(int*,int*);
int a[100010],b[100010],aa[100010],bb[100010],stack[100010],cnt1,cnt2,n;
bool v1[100010],v2[100010];

int main(){
    freopen("bnb.in","r",stdin);
    freopen("bnb.out","w",stdout);
    scanf("%d",&n);
    for (int i=0;i<n;i++) scanf("%d",&a[i]);
    for (int i=0;i<n;i++) scanf("%d",&b[i]);
    sort(a,a+n);
    sort(b,b+n);
    printf("%d %d\n",calc(a,b),n*2-calc(b,a));
    return 0;
}

int calc(int *a,int *b){
    memset(v1,false,sizeof(v1));
    memset(v2,false,sizeof(v2));
    cnt1=cnt2=0;
    int j=n;
    int top=0;
    for (int i=n-1;i>=0;i--){
        while ((j>0)&&(a[j-1]>b[i])) stack[++top]=--j;
        if (top>0){
            v1[stack[top--]]=v2[i]=true;
            ++cnt1;
        }
    }
    int nn=0;
    for (int i=0;i<n;i++) if (!v1[i]) aa[nn++]=a[i];
    top=nn=0;
    for (int i=0;i<n;i++) if (!v2[i]) bb[nn++]=b[i];
    j=nn;
    for (int i=nn-1;i>=0;i--){
        while ((j>0)&&(aa[j-1]>=bb[i])) ++top,--j;
        if (top>0) --top,++cnt2;
    }
    return cnt1*2+cnt2;
}
