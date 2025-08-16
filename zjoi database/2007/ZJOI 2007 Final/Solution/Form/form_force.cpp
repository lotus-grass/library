#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const	int		limitSize	= 10000 + 10;
const	int		infinity	= 1123456789;

struct		Tdat
{
	int	val;
	int	isOrig;
};

bool	operator < (const Tdat& A , const Tdat& B)
{
	return A.val < B.val;
}

int		n , m;
Tdat		list	[limitSize];
Tdat		tmp	[limitSize];

void	init()
{
	scanf("%d%d" , &n , &m);
	for(int i = 0; i < n; i ++)
	{
		scanf("%d" , &list[i].val);
		list[i].isOrig = 1;
	}
	list[n].val = 0;
	list[n].isOrig = 1;
}

void	solve()
{
	char	command	[100];
	int	p , k;
	int	x , i;
	int	ret , curt;

	while(m --)
	{
		scanf("%s" , command);
		if( command[0] == 'I' )		// INSERT
		{
			scanf("%d%d" , &p , &k);
			p ++;
			for(i = 0; i < n; i ++)
			{
				p -= list[i].isOrig;
				if(p == 0) break;
			}
			for(x = n; x > i; x --)
				list[x] = list[x - 1];
			list[i].isOrig = 0;
			list[i].val = k;
			n ++;
		}
		else if( command[4] == 'G' )	// MIN_GAP
		{
			ret = infinity;
			for(i = 1; i < n; i ++)
			{
				curt = abs( list[i].val - list[i - 1].val );
				if( curt < ret ) ret = curt;
			}
			printf("%d\n" , ret);
		}
		else				// MIN_SORT_GAP
		{
			memcpy( tmp , list , sizeof(tmp) );
			sort(tmp , tmp + n);

			ret = infinity;
			for(i = 1; i < n; i ++)
			{
				curt = abs( tmp[i].val - tmp[i - 1].val );
				if( curt < ret ) ret = curt;
			}
			printf("%d\n" , ret);
		}
	}
}

int	main()
{
	freopen("form.2.in" , "r" , stdin);
//	freopen("force.out" , "w" , stdout);

	init();
	solve();

	return 0;
}
