#include <cstdio>
#include <cstring>

const	int		limitSize	= 200 + 10;

int			n;
int			mat	[limitSize][limitSize];

int			cx	[limitSize];
int			cy	[limitSize];
bool			mark	[limitSize];

void	init()
{
	int		i , j;

	scanf("%d" , &n);

	for(i = 0; i < n; i ++)
		for(j = 0; j < n; j ++)
			scanf("%d" , &mat[i][j]);
}

bool	extendPath(int u)
{
	for(int v = 0; v < n; v ++)
		if( mat[u][v] && ! mark[v] )
		{
			mark[v] = 1;
			if( cy[v] < 0 || extendPath( cy[v] ) )
				return cx[u] = v , cy[v] = u , 1;
		}
	return 0;
}

void	solve()
{
	memset(cx , 0xff , sizeof(cx));
	memset(cy , 0xff , sizeof(cy));

	int		i , j;
	for(i = 0; i < n; i ++)
		for(j = 0; j < n; j ++)
			if( cx[i] < 0 && cy[j] < 0 && mat[i][j] )
			{
				cx[i] = j; cy[j] = i; break;
			}
	
	for(i = 0; i < n; i ++)
		if( cx[i] < 0 )
		{
			memset(mark , 0 , sizeof(mark));

			if( ! extendPath( i ) )
			{
				puts("No"); return ;
			}
		}
	
	puts("Yes");
}

int	main()
{
	freopen("matrix.in" , "r" , stdin);
	freopen("matrix.out" , "w" , stdout);

	int		cntCase;

	for( scanf("%d" , &cntCase); cntCase > 0; cntCase -- )
	{
		init();
		solve();
	}

	return 0;
}
