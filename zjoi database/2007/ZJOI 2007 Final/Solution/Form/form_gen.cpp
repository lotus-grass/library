#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <Set>
using namespace std;

const	int		limitSize	= 500000 + 10;
const	int		MAX_RANGE	= 435123234;

int			N[]	= { 10 , 100 , 1000 , 10000 - 1 , 70000 - 1 , 150000 - 1 , 240000 - 1 , 490000 - 1 , 500000 - 1 , 500000 - 1 };
int			M[]	= { 20 , 500 , 5000 , 10000 - 1 , 70000 - 1 , 500000 - 1 , 500000 - 1 , 490000 - 1 , 500000 - 1 , 250000 - 1 };
char			fileName[]	= "form.*.in";

int			list	[limitSize];
int			n , m;
int			gap , start;

void	randTrickIt();

void	randInsert()
{

		int	p = (long long)rand() * rand() % ( n - 1 );
		int	v;
		if( abs( list[p + 1] - list[p] ) > gap * 2 )
		{
			printf("INSERT %d %d\n" , p + 1 , v = min( list[p] , list[p + 1] ) + gap / 2 + rand() % (gap / 10+1) );
		}
		else if( abs( list[p + 1] - list[p] ) > gap )
		{
			printf("INSERT %d %d\n" , p + 1 , v = min( list[p] , list[p + 1] ) + gap / 2 + rand() % (gap / 10+1) );
		}
		else
		{
			printf("INSERT %d %d\n" , p + 1 , v = min( MAX_RANGE , max( list[p] , list[p + 1] ) + gap * 2 + rand() % (gap / 10+1) ) );
		}

		m --; list[p] = v;
}

void	randTrickIt()
{
	int	p;
	int	v;

	for(int t = 10; t >= 0; t --)
	{
		p = (long long)rand() * rand() % ( n - 1 );
		if( abs( list[p + 1] - list[p] ) > gap || t == 0 )
		{
			printf("INSERT %d %d\n" , p + 1 , v = list[p + 1] + (rand() % 3 - 1) * (rand() % (gap / 5 + 1)) );
			m --;
			if( m == 0 ) return;

			puts("MIN_GAP");
			m --;
			if( m == 0 ) return;

			if( rand() % 5 == 0 ){ puts("MIN_SORT_GAP"); m --; }
			
			if( m == 0 ) return;

			printf("INSERT %d %d\n" , p + 1 , v = list[p] + (rand() % 11 - 5) * 2);

			m --; list[p] = v;

			break;
		}
	}
}

void	genCase(int idx , int n0 , int m0)
{
	n = n0; m = m0;

	fileName[5] = idx + '0';
	freopen(fileName , "w" , stdout);

	printf("%d %d\n" , n , m);

	start = rand() % 150;
	gap = MAX_RANGE / n;

	int		i , p , t;

	for(i = 0; i < n; i ++)
	{
		list[i] = start;
		start += gap + (rand() % 3 - 1) * 2;
	}

	for(i = 0; i < n; i ++)
	{
		p = (long long)rand() * rand() % n;
		t = list[i]; list[i] = list[p]; list[p] = t;
	}

	for(i = 0; i < n; i ++)
	{
		if( i ) putchar(' ');
		if( i && list[i] == list[i - 1] ) fprintf(stderr , "shit");
		printf("%d" , list[i]);
	}
	putchar('\n');

	while(m > 0)
	{
		if( rand() % 10 < 4 )
			randInsert();
		else if( rand() % 2 )
			randTrickIt();
		else
		{
			m --;
			if( rand() % 2 ) puts("MIN_GAP");
			else puts("MIN_SORT_GAP");
		}
	}
}

int	main()
{
	
	srand( 19871202 );

	fprintf(stderr , "Start to generating *form* data\n");
	for(int caseNo = 0; caseNo < 10; caseNo ++)
	{
		fprintf(stderr , "Generating case %d.." , caseNo);
		genCase( caseNo , N[ caseNo ] , M[ caseNo ] );
		fprintf(stderr , "\n");
	}
	fprintf(stderr , "Done!!!\n");

	return 0;
}
