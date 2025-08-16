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
#define MOD 19901013
int N, M;
int mat[25][25];
int ans[25][25][25][25];
int tmp[25][25][1 << 15];
int lg[(1 << 15) + 5];
#define lowbit(x) ((x) & -(x))
inline int genList(int x, int *p) {
   int ret = 0;
   while (x) {
      p[ret ++] = lg[lowbit(x)] + 1;
      x ^= lowbit(x);
   }
   return ret;
}
int main() {
   int i, j, k, l, r, u;
   freopen("domino.in", "r", stdin);
   freopen("domino.out", "w", stdout);
   scanf("%d%d", &N, &M);
   for (i = 0; i <= 15; i ++)
      lg[1 << i] = i;
   for (i = 0; i < N; i ++) {
      char tmp1[25];
      scanf("%s", tmp1);
      for (j = 0; j < M; j ++)
	 mat[i][j] = (tmp1[j] == '.' ? 1 : 0);
   }
   for (l = 0; l < M; l ++)
      for (r = l + 1; r <= M; r ++)
	 for (u = 0; u < N; u ++) {
	    int width = r - l;
	    int mask = (1 << width);
	    for (i = 0; i < mask; i ++)
	       tmp[u + 1][l][i] = 1;
	    for (i = u; i >= 0; i --) {
	       for (j = r - 1; j >= l; j --) {
		  int *prev = (j == r - 1 ? tmp[i + 1][l] : tmp[i][j + 1]);
		  int *cnt = &tmp[i][j][0];
		  if (!mat[i][j])
		     for (k = 0; k < mask; k ++, cnt ++)
			*cnt = prev[(k << 1) & (mask - 1)];
		  else
		     if (mat[i - 1][j] && mat[i][j - 1] && j > l) {
			for (k = 0; k < (mask >> 1); k ++, cnt ++) {
			   *cnt = prev[(k << 1) & (mask - 1)] + prev[(k << 1) + 1];
			   if (!(k & 1)) {
			      *cnt += prev[((k << 1) + 3) & (mask - 1)];
			      *cnt %= MOD;
			   }
			}
			for (; k < mask; k ++, cnt ++) {
			   *cnt = prev[(k << 1) & (mask - 1)];
			   if (!(k & 1)) {
			      *cnt += prev[((k << 1) + 3) & (mask - 1)];
			      *cnt %= MOD;
			   }
			}
		     }
		     else
			if (mat[i - 1][j]) {
			   for (k = 0; k < (mask >> 1); k ++, cnt ++)
			      *cnt = (prev[(k << 1) & (mask - 1)] + prev[(k << 1) + 1]) % MOD;
			   for (; k < mask; k ++, cnt ++)
			      *cnt = prev[(k << 1) & (mask - 1)];
			}
			else
			   if (mat[i][j - 1] && j > l)
			      for (k = 0; k < mask; k ++, cnt ++) {
				 *cnt = prev[(k << 1) & (mask - 1)];
				 if (!(k & 1)) {
				    *cnt += prev[((k << 1) + 3) & (mask - 1)];
				    *cnt %= MOD;
				 }
			      }
			   else
			      for (k = 0; k < mask; k ++, cnt ++)
				 *cnt = prev[(k << 1) & (mask - 1)];
	       }
	       ans[l][r][i][u + 1] = tmp[i][l][mask - 1];
	    }
	 }
   int list1[25], len1;
   long long ret = 0;
   for (i = 0; i < (1 << M - 1); i ++) {
      list1[0] = 0;
      len1 = genList(i, list1 + 1) + 1;
      list1[len1] = M;
      long long tmp2[25];
      tmp2[N] = (len1 % 2 ? -1 : 1);
      for (j = N - 1; j >= 0; j --) {
	 tmp2[j] = 0;
	 for (k = j + 1; k <= N; k ++) {
	    long long tmp3 = 1;
	    for (l = 0; l < len1; l ++) {
	       tmp3 *= ans[list1[l]][list1[l + 1]][j][k];
	       tmp3 %= MOD;
	    }
	    tmp2[j] -= tmp3 * tmp2[k];
	 }
	 tmp2[j] %= MOD;
      }
      ret += tmp2[0];
   }
   ret %= MOD;
   ret += MOD;
   ret %= MOD;
   printf("%d\n", (int)ret);
   return 0;
}
