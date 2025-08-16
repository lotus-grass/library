/*
 *	Problem		:	Knight, ZJOI 2008
 *	Date		:	2008-3-17
 *	Algorithm	:	DP
 *	Author		:	
 *
 */

#include <iostream>

using namespace std;

const int	maxN	= 1000000 + 100;

typedef long long int64;

int	power[maxN], hate[maxN], inD[maxN], stack[maxN], circle[maxN];
int64	opt[maxN][2];

int	N, top;

int	main()
{
	freopen("knight.in" , "r" , stdin);
	freopen("knight.out" , "w" , stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%d%d", &power[i], &hate[i]), --hate[i];

	memset(opt, 0, sizeof(opt));
	
	memset(inD, 0, sizeof(inD));	//	in degree
	for (int i = 0; i < N; ++i) ++inD[hate[i]];

	//	process nodes in tree structure

	top = 0;
	for (int i = 0; i < N; ++i) if (!inD[i]) stack[top++] = i;

	while (top)
	{
		int u = stack[--top], v = hate[u];

		opt[u][1] += power[u]; 
		opt[v][1] += opt[u][0];
		opt[v][0] += max(opt[u][1], opt[u][0]);

		--inD[v];
		if (!inD[v]) stack[top++] = v;
	}

	//	process nodes in circle structure

	int64 totPower = 0;

	for (int i = 0; i < N; ++i) if (inD[i])	//	node i lays in circle
	{
		int len = 0, u = i;
		do {
			opt[u][1] += power[u];
			circle[len++] = u;
			inD[u] = 0;
			u = hate[u];
		}	while (inD[u]);

//		for (int j = 0; j < len; ++j) cout << opt[circle[j]][0] << ' ' << opt[circle[j]][1] << ' '; cout << endl;

		int64 x = opt[circle[len - 1]][0], y = 0;
		for (int i = 0; i < len - 1; ++i)
		{
			int u = circle[i];
			int64 nx = max(x, y) + opt[u][0], ny = x + opt[u][1];
			x = nx; y = ny;
		}
		int64 dropN = max(x, y);

		x = opt[circle[0]][0]; y = 0;
		for (int i = 1; i < len; ++i)
		{
			int u = circle[i];
			int64 nx = max(x, y) + opt[u][0], ny = x + opt[u][1];
			x = nx; y = ny;
		}
		int64 drop1 = max(x, y);

		totPower += max(drop1, dropN);
	}

	printf("%I64d\n", totPower);

	return 0;
}
