#include <cstdio>
#include <cstring>
#include <cstdlib>

const	int	limitSize	= 1000000 + 10;
char		fileName[]	= "synch.*.in";

int	N[]	= {12 , 33 , 249 , 923 , 6342 , 235232 , 412342 , 434532 , 423423 , 399999};

inline	int	myRand()
{
	return	( rand() << 15 ) + rand();
}

int		list	[limitSize];

void	genRandSeq(int n)
{
	int	i , j , t;

	for(i = 0; i < n; i ++)
		list[i] = i;
	for(i = 0; i < n; i ++)
	{
		j = myRand() % n;
		t = list[i]; list[i] = list[j]; list[j] = t;
	}
	for(i = 0; i < n; i ++)
	{
		j = myRand() % n;
		t = list[i]; list[i] = list[j]; list[j] = t;
	}
}

void	genNormalCase(int n)
{
	printf("%d\n%d\n" , n , list[ myRand() % n ] + 1);

	int	i;
	for(i = 1; i < n; i ++)
	{
		printf("%d %d %d\n" , list[i] + 1 , list[myRand() % i] + 1 , myRand() % 1000000 + 1 );
	}
}

void	genLineCase(int n)
{
	int		line = n / 3 + myRand() % (n / 3);
	int		i;

	printf("%d\n%d\n" , n , list[ 0 ] + 1);

	for(i = 1; i <= line; i ++)
	{
		printf("%d %d %d\n" , list[i - 1] + 1 , list[i] + 1 , myRand() % 1000000 + 1 );
	}
	for( ; i < n; i ++)
	{
		printf("%d %d %d\n" , list[i] + 1 , list[myRand() % i] +  1, myRand() % 10000 + 1 );
	}
}

void	genCase(int idx , int n)
{
	fileName[6] = '0' + idx;
	freopen(fileName , "w" , stdout);

	genRandSeq(n);

	if( idx < 7 ) genNormalCase(n);
	else genLineCase(n);
}

int	main()
{
	srand( 19871202 );

	fprintf(stderr , "Start to generating *synch* data\n");
	for(int caseNo = 0; caseNo < 10; caseNo ++)
	{
		fprintf(stderr , "Generating case %d.." , caseNo);
		genCase( caseNo , N[ caseNo ] );
		fprintf(stderr , "\n");
	}
	fprintf(stderr , "Done!!!\n");


	return 0;
}
