#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int modnum=12345678;
const int maxn=160;
const int maxk=22;

int n, m, k;
int f[maxn][maxn][maxk][maxk];

void getinfo() {
	scanf("%d%d%d",&n,&m,&k);
	memset(f,0,sizeof(f));
}

void work() {
	f[0][0][0][0]=1;
	for (int i=0; i<=n; i++)
		for (int j=0; j<=m; j++)
			for (int k1=0; k1<=k; k1++)
				for (int k2=0; k2<=k; k2++)
					if (f[i][j][k1][k2]!=0) {
						if ((i==n)&&(j==m)) continue;
						int c=(i+1-j);
						if (c>0)
							f[i+1][j][max(c,k1)][k2]=(f[i+1][j][max(c,k1)][k2]+f[i][j][k1][k2])%modnum;
						else
							f[i+1][j][k1][max(-c,k2)]=(f[i+1][j][k1][max(-c,k2)]+f[i][j][k1][k2])%modnum;
						c=(i-j-1);
						if (c>0)
							f[i][j+1][max(c,k1)][k2]=(f[i][j+1][max(c,k1)][k2]+f[i][j][k1][k2])%modnum;
						else
							f[i][j+1][k1][max(-c,k2)]=(f[i][j+1][k1][max(-c,k2)]+f[i][j][k1][k2])%modnum;
					}
}

void out() {
	int ans=0;
	for (int i=0; i<=k; i++)
		for (int j=0; j<=k-i; j++)
			ans=(ans+f[n][m][i][j])%modnum;
	printf("%d\n",ans);
}

int main() {

	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
	
	getinfo();
	work();
	out();
	
	return 0;
}

