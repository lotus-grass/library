#include <fstream>
using namespace std;

const char *inputfilename = "foldgirl.in0", 
		   *outputfilename = "foldgirl.ou0";
const int maxn = 500, maxm = 500, maxt = maxn * maxm;

typedef int array[maxn + 1][maxm + 1];
array map, pam;

int t, n, m, link[maxt + 1];

void newarc(int x, int y)
{
	if (x < y)
	{
		link[x] = y; link[y] = -1;
	}
	else
	{
		link[y] = x; link[x] = -1;
	}
}

bool check(int n, int m, array &map, int x)
{
	int i, j, top, stack[maxt + 1];
	memset(link, 0, sizeof(link));
	for (i = 1; i <= n - 1; i++)
		if ((i & 1) == x)
			for (j = 1; j <= m; j++) newarc(map[i][j], map[i + 1][j]);

	top = 0;
	for (i = 1; i <= t; i++)
	{
		if (link[i] > 0)
		{
			top++; stack[top] = link[i];
		}
		else if (link[i] < 0)
		{
			if (stack[top] != i) return(false);
			top--;
		};
	}
	return(true);
}

void main()
{
	ifstream fin(inputfilename);
	ofstream fout(outputfilename);
	int testcases, k, i, j;
	fin >> testcases;

	for (k = 1; k <= testcases; k++)
	{
		fin >> n >> m;
		t = n * m;
		for (i = 1; i <= n; i++)
			for (j = 1; j <= m; j++) 
			{
				fin >> map[i][j]; pam[j][i] = map[i][j];
			}
		if (check(n, m, map, 0) && check(n, m, map, 1) &&
		    check(m, n, pam, 0) && check(m, n, pam, 1)) fout << "AllRight" << endl;
		else fout << "Cheat" << endl;
	}
	fin.close(); fout.close();
}
