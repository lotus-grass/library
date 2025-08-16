#include <fstream.h>
#include <stdlib.h>

void main()
{
  ofstream fn("input.txt");
  int i, n =1000, v[1000];
  randomize();
  n=random(1000)+1;
  fn << n << '\n';
  for (i = 0; i < n; i ++) v[i] = i + 1;
  for (i = 0; i < n * n; i ++)
  {
    int x = random(n), y = random(n);
    int k = v[x]; v[x] = v[y]; v[y] = k;
  }
  for (i = 0; i < n; i ++) fn << v[i] << ' ';
  fn << '\n';
  fn.close();
}
