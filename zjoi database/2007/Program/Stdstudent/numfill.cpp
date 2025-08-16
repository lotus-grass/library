//j

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn=1010;
int n;
int a[maxn];

int getv(int x){
    if (x>=0) return x;
    return -x;
}

void work(){
     int i,j,k,v;
     
     if (n%4==2 || n%4==1) return;
     j=1;k=n;
     for (i=1;i<=n;++i)
         if (i%2==1) a[i]=j++;
         else a[i]=k--;
     
     v=getv(a[n]-a[1]);
     for (i=1;i<=n-1;++i)
         if (getv(a[i]-a[i+1])==v) break;
         
     while (i>0){
           ++a[i];
           i-=2;
     }
     
}

void print(int ee){
     int i;
     
//     printf("Case %d:",ee);
     
 /*    if (n==2){
        printf(" %d %d\n",1,3);
        return;
     }*/
     
     if (n%4==2 || n%4==1) {
                printf("No\n");
                return;
     }
     
     printf("Yes\n");
     for (i=1;i<=n;++i)
         printf("%d ",a[i]);
     printf("\n");
}

int main(){
    int i;
    
    freopen("numfill.in","r",stdin);
    freopen("numfill.out","w",stdout);
    
    i=0;
    scanf("%d",&n);
//    while (n!=0){
          work();
          print(++i);
//          scanf("%d",&n);
//    }
    
    return 0;
}
