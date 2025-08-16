#include <cstdio>
#include <cstring>

const	int	limitSize	= 150 + 10;
const	int	limitLeng	= 24;
const	int	M		= 12345678;

int		n , m , k;

int		opt	[limitSize][limitSize][limitLeng][limitLeng];

void	solve()
{
	memset(opt , 0 , sizeof(opt));
	opt[0][0][0][0] = 1;

	int	i , j , a , b , na , nb;
	for (i = 0; i <= n; i ++)
		for (j = 0; j <= m; j ++)
			for (a = 0; a <= k; a ++)
				for (b = 0; b <= k; b ++)
	{
		if (opt[i][j][a][b] == 0) continue;
		na = a + 1; nb = b - 1;
		if (na <= k)
		{
			if (nb < 0) nb = 0;
			opt[i+1][j][na][nb] = ( opt[i+1][j][na][nb] + opt[i][j][a][b] ) % M;
		}
		na = a - 1; nb = b + 1;
		if (nb <= k)
		{
			if (na < 0) na = 0;
			opt[i][j+1][na][nb] = ( opt[i][j+1][na][nb] + opt[i][j][a][b] ) % M;
		}
	}

	int		ret = 0;
	for (a = 0; a <= k; a ++)
		for (b = 0; b <= k; b ++)
			ret = (ret + opt[n][m][a][b]) % M;
	printf("%d\n" , ret);
}

int	main()
{
	freopen("party.in" , "r" , stdin);
	freopen("party.out" , "w" , stdout);

	scanf("%d%d%d" , &n , &m , &k);
	solve();

	return 0;
}
