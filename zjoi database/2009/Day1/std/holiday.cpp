#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
using namespace std;
#define PI 3.14159265358979323846264338327950288
int N, T;
int mat[105][105];
int stud[105], goh[105];
int newid[2][105];
int n1, n2;
int graph[105][105];
int ans;
int mark[105];
int o2[105];
int dfs(int x) {
   int i;
   mark[x] = 1;
   for (i = 0; i < n2; i ++)
      if (graph[x][i] && (o2[i] == -1 || !mark[o2[i]] && dfs(o2[i]))) {
	 o2[i] = x;
	 return 1;
      }
   return 0;
}
int main() {
   int i, j;
   freopen("holiday.in", "r", stdin);
   freopen("holiday.out", "w", stdout);
   scanf("%d", &T);
   while (T --) {
      scanf("%d", &N);
      for (i = 0; i < N; i ++)
	 scanf("%d", &stud[i]);
      for (i = 0; i < N; i ++)
	 scanf("%d", &goh[i]);
      for (i = 0; i < N; i ++)
	 for (j = 0; j < N; j ++)
	    scanf("%d", &mat[i][j]);
      n1 = n2 = 0;
      for (i = 0; i < N; i ++) {
	 if (stud[i])
	    newid[0][n1 ++] = i;
	 if (!stud[i] || !goh[i])
	    newid[1][n2 ++] = i;
      }
      for (i = 0; i < n1; i ++)
	 for (j = 0; j < n2; j ++)
	    graph[i][j] = (mat[newid[0][i]][newid[1][j]] || newid[0][i] == newid[1][j]);
      ans = 0;
      memset(o2, -1, sizeof(o2));
      for (i = 0; i < n1; i ++) {
	 memset(mark, 0, sizeof(mark));
	 if (dfs(i))
	    ans ++;
      }
      if (ans == n2)
	 printf("^_^\n");
      else
	 printf("T_T\n");
   }
   return 0;
}

