//ZJOI2010 count Accepted
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <string>
#include <functional>
#include <queue>
using namespace std;
#define clavichord
#define MP(a,b) make_pair(a,b)
#define MS(a,b) memset(a,b,sizeof(a))
#define MC(a,b) memcpy(a,b,sizeof(b))
#define sqr(a) (a)*(a)
#define npos string::npos
#define filename "count"
template<class T> inline void gmin(T &a,T b) {
	if(a>b) a=b;
}
template<class T> inline void gmax(T &a,T b) {
	if(a<b) a=b;
}
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
typedef long long ll;
typedef unsigned long long ull;
const int INF=0x3f3f3f3f;
const double EPS=1e-10;
const double PI=3.14159265358979323846264338327950288;
const int SIZE=999987;
const int SEED=131;
inline int dcmp(double a) {
	return a>EPS?1:(a<-EPS?-1:0);
}

const int MN=15;

ll l,r;
ll num[MN],ans[MN];
ll f[MN][MN][MN];
ll power[MN];

void init() {
	power[0]=1;
	for(int i=1;i<=13;i++) power[i]=power[i-1]*10LL;
	
	MS(f,0);
	for(int i=0;i<=9;i++) f[1][i][i]=1;
	for(int i=2;i<=13;i++)
		for(int j=0;j<=9;j++)
			for(int k=0;k<=9;k++) {
				for(int p=0;p<=9;p++) f[i][j][k]+=f[i-1][p][k];
				if(j==k) f[i][j][k]+=power[i-1];
			}
}

ll calc(int lab,ll x) {
	int n=0;
	ll x1=x;
	while(x1) {
		num[++n]=x1%10;
		x1/=10;
	}
	ll rec=0;
	for(int i=n;i;i--) {
		for(int j=0;j<=num[i]-1;j++) rec+=f[i][j][lab];
		if(num[i]==lab) rec+=x%power[i-1]+1LL;
	}
	if(!lab) {
		for(int i=1;i<=n;i++) rec-=power[i-1];
	}
	return rec;
}

int main() {
	freopen(filename".in","r",stdin);
	freopen(filename".out","w",stdout);
	
	init();
	cin >> l >> r;
	for(int i=0;i<=9;i++) ans[i]=calc(i,r)-calc(i,l-1);
	for(int i=0;i<9;i++) cout << ans[i] << ' ';
	cout << ans[9] << endl;
	
	fclose(stdin); fclose(stdout);
	return 0;
}
