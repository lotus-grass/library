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
int N, K;
int main() {
   freopen("function.in", "r", stdin);
   freopen("function.out", "w", stdout);
   scanf("%d%d", &N, &K);
   if (N == 1)
      printf("1\n");
   else
      printf("%d\n", 2 * min(K, N - K + 1));
   return 0;
}

