#include <cstdio>
#include <cstring>

const	int		limitSize	= 2000 + 10;

int			n , m;
int			mat	[limitSize][limitSize];
int			extend	[limitSize][limitSize];
int			extendUp[limitSize][limitSize];

int			f	[limitSize][limitSize];
int			left	[limitSize];
int			right	[limitSize];
int			list	[limitSize];

int			maxRect , maxSquare;

void	init()
{
	int		i , j , k;

	scanf("%d%d" , &n , &m);
	for(i = 0; i < n; i ++)
		for(j = 0; j < m; j ++)
		{
			scanf("%d" , &k);
			if( (i + j) % 2 ) mat[i][j] = k;
			else mat[i][j] = 1 - k;
		}
}

inline	int	min(int a , int b){ return a < b ? a : b; }

void	findSquare()
{
	int		i , j , k;

	for(i = 0; i < n; i ++)
	{
		for(j = k = 0; j < m; j ++)
		{
			if( mat[i][j] ) k ++; else k = 0;
			extend[i][j] = k;
		}
	}
	for(i = 0; i < m; i ++)
	{
		for(j = k = 0; j < n; j ++)
		{
			if( mat[j][i] ) k ++; else k = 0;
			extendUp[j][i] = k;
		}
	}

	for(i = 0; i < n; i ++)
		for(j = 0; j < m; j ++)
		{
			if( i == 0 || j == 0 ) f[i][j] = min(extend[i][j] , extendUp[i][j]);
			else f[i][j] = min( f[i - 1][j - 1] + 1 , min( extend[i][j] , extendUp[i][j] ) );
			if( f[i][j] > maxSquare ) 
				maxSquare = f[i][j];
		}
}

void	findRect()
{
	int		p , i , curt;

	for(p = 0; p < m; p ++)
	{
		for(i = 0; i < n; i ++)
			list[i] = extend[i][p];
		for(i = 0; i < n; i ++)
		{
			left[i] = i;
			while( left[i] > 0 && list[ left[i] - 1 ] >= list[i] )
				left[i] = left[ left[i] - 1 ];
		}
		for(i = n - 1; i >= 0; i --)
		{
			right[i] = i;
			while( right[i] < n - 1 && list[ right[i] + 1 ] >= list[i] )
				right[i] = right[ right[i] + 1 ];
		}
		for(i = 0; i < n; i ++)
		{
			curt = list[i] * (right[i] - left[i] + 1);
			if( curt > maxRect ) maxRect = curt;
		}
	}
}

void	solve()
{
	int		i , j;

	maxRect = maxSquare = 0;

	findSquare(); findRect();

	for(i = 0; i < n; i ++)
		for(j = 0; j < m; j ++)
			mat[i][j] = 1 - mat[i][j];
	
	findSquare(); findRect();

	printf("%d\n" , maxSquare * maxSquare);
	printf("%d\n" , maxRect);
}

int	main()
{
	freopen("chess.in" , "r" , stdin);
	freopen("chess.out" , "w" , stdout);

	init();
	solve();

	return 0;
}
