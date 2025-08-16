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
int N, M, T;
char mat[105][105];
int list[205];
#define lowbit(x) ((x) & -(x))
int lg(int x) {
   return (x == 1 ? 0 : lg(x / 2) + 1);
}
int sg(int x, int y) {
   if (x == 0 || y == 0)
      return lg(lowbit(x + y + 1));
   return x + y;
}
int main() {
   int i, j;
   freopen("game.in", "r", stdin);
   freopen("game.out", "w", stdout);
   scanf("%d", &T);
   while (T --) {
      scanf("%d%d", &N, &M);
      for (i = 0; i < N; i ++)
	 scanf("%s", mat[i]);
      memset(list, 0, sizeof(list));
      for (i = 0; i < N; i ++)
	 for (j = 0; j < M; j ++)
	    if (mat[i][j] == 'T')
	       list[sg(i, j)] ^= 1;
      for (i = 0; i < N + M; i ++)
	 if (list[i])
	    break;
      if (i < N + M)
	 printf("-_-\n");
      else
	 printf("=_=\n");
   }
   return 0;
}

