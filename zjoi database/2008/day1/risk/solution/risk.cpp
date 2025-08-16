//Author:Fluorine
#include <algorithm>
#include <cstdio>
#include <string>
#define prime 31231
using namespace std;

struct Point{
    int x,y;
}point[4010],cap[610];
struct Line{
    int p1,p2;
}line[8010];
struct Poly{
    int p[4010],line[4010],num,fa;
    long long s;
}poly[1210];
struct arr{
    int data;
    arr *next;
}*link[31240];
int de[8010][8010],num[8010],nextline[8010],templine[8010],son[1210][1210],sonnum[1210],lineleft[4010],lineright[4010];
int n,m,pointnum,polynum,temp,cnt,x1,y1,x2,y2;
bool visit[8010],ga[1210][1210];

long long labs(long long x){
    if (x<0LL) return -x;
    return x;
}

int cha(Point a,Point b,Point c){
    long long temp=(long long)(b.x-a.x)*(long long)(c.y-a.y)-(long long)(c.x-a.x)*(long long)(b.y-a.y);
    if (temp==0LL) return 0;
    if (temp>0LL) return 1;
    return -1;
}

int dian(Point a,Point b,Point c){
    long long temp=(long long)(b.x-a.x)*(long long)(c.x-a.x)+(long long)(b.y-a.y)*(long long)(c.y-a.y);
    if (temp==0LL) return 0;
    if (temp>0LL) return 1;
    return -1;
}

int find(int x,int y){
    int temp=(x*1123+y*1327)%prime;
    for (arr *p=link[temp];p!=NULL;p=p->next)
        if ((point[p->data].x==x)&&(point[p->data].y==y)) return p->data;
    point[pointnum].x=x;
    point[pointnum].y=y;
    arr *p=new arr;
    p->data=pointnum++;
    p->next=link[temp];
    link[temp]=p;
    return pointnum-1;
}

void sort1(int num,int m,int n){
    int x=de[num][(m+n)/2],i=m,j=n;
    de[num][(m+n)/2]=de[num][m];
    while (i<j){
        while ((i<j)&&(cha(point[num],point[line[x].p2],point[line[de[num][j]].p2])==1)) j--;
        if (i<j) de[num][i++]=de[num][j];
        while ((i<j)&&(cha(point[num],point[line[x].p2],point[line[de[num][i]].p2])<1)) i++;
        if (i<j) de[num][j--]=de[num][i];
    }
    de[num][i]=x;
    if (m<i-1) sort1(num,m,i-1);
    if (j+1<n) sort1(num,j+1,n);
}

bool cmp(const Poly &a,const Poly &b){
    return a.s>b.s;
}

int inside(Point p1,int y){
    Point p2;
    int sum=0;
    p2.x=20003;
    p2.y=30023;
    for (int i=0;i<poly[y].num;i++){
        if ((p1.x==point[poly[y].p[i]].x)&&(p1.y==point[poly[y].p[i]].y)) return 0;
        if ((cha(p1,point[poly[y].p[i]],point[poly[y].p[i+1]])==0)&&(dian(p1,point[poly[y].p[i]],point[poly[y].p[i+1]])==-1)) return 0;
        if ((cha(p1,p2,point[poly[y].p[i]])*cha(p1,p2,point[poly[y].p[i+1]])==-1)&&(cha(point[poly[y].p[i]],point[poly[y].p[i+1]],p1)*cha(point[poly[y].p[i]],point[poly[y].p[i+1]],p2)==-1)) sum++;
    }
    if (sum%2) return 1;
    return -1;
}

bool check(int x,int y){
    for (int i=0;i<poly[x].num;i++){
        int temp=inside(point[poly[x].p[i]],y);
        if (temp==1) return true;
        if (temp==-1) return false;
    }
    return true;
}

int dfs(Point p,int x){
    for (int i=0;i<sonnum[x];i++) if (inside(p,son[x][i])==1) return dfs(p,son[x][i]);
    return x;
}

void update(int x,int y){
    if (lineleft[y]==-1) lineleft[y]=x;
    else if (lineleft[y]!=x) lineright[y]=x;
}

int main(){
    freopen("risk.in","r",stdin);
    freopen("risk.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d%d",&cap[i].x,&cap[i].y);
    for (int i=0;i<prime;i++) link[i]=NULL;
    pointnum=polynum=0;
    for (int i=0;i<m;i++){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        line[i*2].p1=find(x1,y1);
        line[i*2].p2=find(x2,y2);
        line[i*2+1].p1=line[i*2].p2;
        line[i*2+1].p2=line[i*2].p1;
    }
    memset(num,0,sizeof(num));
    for (int i=0;i<m*2;i++) de[line[i].p1][num[line[i].p1]++]=i;
    for (int i=0;i<pointnum;i++) sort1(i,0,num[i]-1);
    for (int i=0;i<pointnum;i++){
        for (int j=1;j<num[i];j++)
            if (de[i][j]%2) nextline[de[i][j]-1]=de[i][j-1];
            else nextline[de[i][j]+1]=de[i][j-1];
        if (de[i][0]%2) nextline[de[i][0]-1]=de[i][num[i]-1];
        else nextline[de[i][0]+1]=de[i][num[i]-1];
    }
    memset(visit,false,sizeof(visit));
    for (int i=0;i<m*2;i++){
        cnt=0;
        for (int j=i;!visit[j];j=nextline[j]) visit[templine[cnt++]=j]=true;
        for (int j=0;j<cnt;j++)
            if (templine[j]==nextline[templine[cnt-1]]){
                poly[polynum].num=0;
                for (int k=j;k<cnt;k++){
                    poly[polynum].line[poly[polynum].num]=templine[k];
                    poly[polynum].p[poly[polynum].num++]=line[templine[k]].p2;
                }
                poly[polynum].p[poly[polynum].num]=poly[polynum].p[0];
                polynum++;
                break;
            }
    }
    point[pointnum].x=-20000;
    point[pointnum].y=-20000;
    point[pointnum+1].x=20000;
    point[pointnum+1].y=-20000;
    point[pointnum+2].x=20000;
    point[pointnum+2].y=20000;
    point[pointnum+3].x=-20000;
    point[pointnum+3].y=20000;
    poly[polynum].num=4;
    poly[polynum].p[0]=pointnum;
    poly[polynum].p[1]=pointnum+1;
    poly[polynum].p[2]=pointnum+2;
    poly[polynum].p[3]=pointnum+3;
    poly[polynum].p[4]=pointnum;
    polynum++;
    for (int i=0;i<polynum;i++){
        poly[i].s=0LL;
        for (int j=0;j<poly[i].num;j++) poly[i].s+=(long long)point[poly[i].p[j]].x*(long long)point[poly[i].p[j+1]].y-(long long)point[poly[i].p[j+1]].x*(long long)point[poly[i].p[j]].y;
        poly[i].s=labs(poly[i].s);
    }
    sort(poly,poly+polynum,cmp);
    memset(sonnum,0,sizeof(sonnum));
    for (int i=polynum-1;i>0;i--){
        for (int j=i-1;j>=0;j--)
            if (check(i,j)){
                poly[i].fa=j;
                son[j][sonnum[j]++]=i;
                break;
            }
    }
    memset(lineleft,-1,sizeof(lineleft));
    memset(lineright,-1,sizeof(lineright));
    memset(ga,false,sizeof(ga));
    for (int i=1;i<=n;i++){
        temp=dfs(cap[i],0);
        for (int j=0;j<poly[temp].num;j++) update(i,poly[temp].line[j]/2);
        for (int j=0;j<sonnum[temp];j++)
            for (int k=0;k<poly[son[temp][j]].num;k++)
                update(i,poly[son[temp][j]].line[k]/2);
    }
    for (int i=0;i<m;i++) if (lineright[i]!=-1) ga[lineleft[i]][lineright[i]]=ga[lineright[i]][lineleft[i]]=true;
    for (int i=1;i<=n;i++){
        cnt=0;
        for (int j=1;j<=n;j++) if (ga[i][j]) cnt++;
        printf("%d",cnt);
        for (int j=1;j<=n;j++) if (ga[i][j]) printf(" %d",j);
        printf("\n");
    }
    return 0;
}
