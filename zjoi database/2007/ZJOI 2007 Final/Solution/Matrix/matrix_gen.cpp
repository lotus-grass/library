#include <cstdio>
#include <cstring>
#include <cstdlib>

const	int	limitSize	= 200 + 10;
char		fileName[]	= "matrix.*.in";

int	N[]	= {4 , 7 , 15 , 30 , 50 , 90 , 120 , 180 , 200 , 200};
int	T[]	= {5 , 7 , 12 , 12 , 12 , 18 , 18 , 20 , 20 , 20};

int		mat	[limitSize][limitSize];

inline	void	swap(int& a , int& b)
{
	int	t;
	t = a; a = b; b = t;
}

inline	int	min(int a , int b){ return a < b ? a : b; }

void	printMatrix(int n)
{
	int	r , c , i , j , k;
	int	v;

	for(int shuffle = 0; shuffle < 2; shuffle ++)
	{
		r = c = 0;
		while( r < n && c < n )
		{
			if( r == n ) v = 1;
			else if( c == n ) v = 0;
			else v = rand() % 2;

			k = rand() % n;
			if( v == 0 )
			{
				for(i = 0; i < n; i ++)
					swap( mat[r][i] , mat[k][i] );
				r ++;
			}
			else
			{
				for(i = 0; i < n; i ++)
					swap( mat[i][c] , mat[i][k] );
				c ++;
			}
		}
	}

	printf("%d\n" , n);

	for(i = 0; i < n; i ++)
	{
		for(j = 0; j < n; j ++)
		{
			if( j ) putchar(' ');
			printf("%d" , mat[i][j]);
		}
		putchar('\n');
	}
}

void	genNoCase(int n)
{
	int	i , j;

	memset(mat , 0 , sizeof(mat));	
	for(i = 0; i < n; i ++)
		mat[i][j] = 1;
	for(i = 0; i * i < n; i ++)
	{
		j = rand() % n;
		mat[j][j] = 0;
	}
	for(i = 0; i < min(n * 3 , n * n / 3); i ++)
		mat[ rand() % n ][ rand() % n ] = 1;

	printMatrix(n);
}

void	genYesCase(int n)
{
	int	i;

	memset(mat , 0 , sizeof(mat));
	for(i = 0; i < n; i ++)
		mat[i][i] = 1;
	for(i = 0; i < min(n * 3 , n * n / 3); i ++)
		mat[ rand() % n ][ rand() % n ] = 1;

	printMatrix(n);
}

void	genRandCase(int n)
{
	int	i , j;

	for(i = 0; i < n; i ++)
		for(j = 0; j < n; j ++)
			mat[i][j] = 1 - ( rand() % 6 ? 0 : 1 );

	printMatrix(n);
}

void	genCase(int id , int n , int cntCase)
{
	fileName[7] = '0' + id;
	freopen(fileName , "w" , stdout);

	printf("%d\n" , cntCase);

	if( id >= 3 )
	{
		cntCase --;
		puts("3");
		puts("0 1 0");
		puts("1 0 1");
		puts("0 1 0");
	}

	int		tn;

	while( cntCase -- )
	{
		fprintf(stderr , ".");

		tn = n;
		if( rand() % 3 ) tn -= rand() % (n / 2);
		
		if( rand() % 7 < 3 )
			genNoCase(tn);
		else if( rand() % 6 < 4 )
			genYesCase(tn);
		else	genRandCase(tn);
	}
}

int	main()
{
	srand( 19871202 );

	fprintf(stderr , "Start to generating *matrix* data\n");
	for(int caseNo = 0; caseNo < 10; caseNo ++)
	{
		fprintf(stderr , "Generating case %d.." , caseNo);
		genCase( caseNo , N[ caseNo ] , T[ caseNo ] );
		fprintf(stderr , "\n");
	}
	fprintf(stderr , "Done!!!\n");


	return 0;
}
