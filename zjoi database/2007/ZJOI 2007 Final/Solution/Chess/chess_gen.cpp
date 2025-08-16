#include <cstdio>
#include <cstring>
#include <cstdlib>

const	int	limitSize	= 2000 + 10;

char		fileName[]	= "chess.*.in";

int	N[] = {10 , 60 , 200 , 400 , 700 , 900 , 1500 , 1900 , 2000 , 2000};
int	M[] = {13 , 80 , 100 , 400 , 200 , 1200 , 1700 , 1000 , 2000 , 2000};

int	mat	[limitSize][limitSize];

inline	int	min(int a , int b){ return a < b ? a : b; }

inline	int	myRand(int v)
{
	return rand() % (v / 2 + 1) + v / 2;
}

void	genCase(int idx , int n , int m)
{
	fileName[6] = '0' + idx;
	freopen(fileName , "w" , stdout);

	printf("%d %d\n" , n , m);
	memset(mat , 0xff , sizeof(mat));
	
	int	x , y;
	int	i , j;
	int	lx , ly;
	int	v;

	for(int t = 0; t < 100 + rand() % 100; t ++)
	{
		if( t % 10 == 0 ) fprintf(stderr , ".");
		x = rand() % n;
		y = rand() % m;

		lx = myRand( n - x );
		ly = myRand( m - y );

		v = rand() % 2;
		for(i = 0; i < lx; i ++)
			for(j = 0; j < ly; j ++)
			{
				if( (i + j) % 2 ) mat[x + i][y + j] = v;
				else mat[x + i][y + j] = 1 - v;
			}
	}

	for(i = 0; i < n; i ++)
	{
		for(j = 0; j < m; j ++)
		{
			if( j ) putchar(' ');
			if( mat[i][j] < 0 ) mat[i][j] = rand() % 2;
			printf("%d" , mat[i][j]);
		}
		putchar('\n');
	}
}

int	main()
{
	srand( 19871202 );

	fprintf(stderr , "Start to generating *chess* data\n");
	for(int caseNo = 0; caseNo < 10; caseNo ++)
	{
		fprintf(stderr , "Generating case %d.." , caseNo);
		genCase( caseNo , N[ caseNo ] , M[ caseNo ] );
		fprintf(stderr , "\n");
	}
	fprintf(stderr , "Done!!!\n");
	
	return 0;
}
