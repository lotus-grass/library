#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const	int		limitQuery	= 500000 + 10;
const	int		limitSize	= 500000 + 10 + limitQuery;
const	int		infinity	= 1123456789;

struct		Tquery
{
	int	type;
	int	i , k;
	int	pos;			// 该元素排序后的位置
	int	resp;
};

struct		TsortDat
{
	int	key;
	int	from;			// 是第几个输入
};
bool	operator < (const TsortDat& A , const TsortDat& B)
{
	return A.key < B.key;
}

int			n , m , sortN;
int			orig	[limitSize];
Tquery			query	[limitQuery];
TsortDat		sortSeq	[limitSize];

int			extend	[limitSize];
int			final	[limitSize];

struct		TheapDat
{
	int		key;
	int		from;
};

struct		Theap
{
	int		list	[limitSize];
	int		prev	[limitSize];
	int		next	[limitSize];

	int		heapSize;
	TheapDat	heap	[limitSize];
	int		pos	[limitSize];

	void	init()
	{
		int	i;

		for(i = 0; i <= n + 1; i ++)
			prev[i] = i - 1 , next[i] = i + 1;

		heapSize = 0;
		for(i = 1; i < n; i ++)
		{
			++ heapSize;
			heap[ heapSize ].key = abs( list[i] - list[i + 1] );
			heap[ heapSize ].from = i;
			pos[ i ] = heapSize;

			heapifyUp( heapSize );
		}
	}

	inline	int	getMin()
	{
		return	heap[ 1 ].key;
	}

	void	kick(int u)
	{
		int	left = prev[u];
		int	right = next[u];
		
		//	delete	pos[ u ]
		//	change	pos[ left ]
		//	renew prev , next

		if( right > n )
		{
			heap[ pos[left] ] = heap[ heapSize ];
			pos[ heap[ pos[left] ].from ] = pos[ left ];
			heapSize --;

			if( pos[ left ] <= heapSize )
			{
				heapifyDown( pos[left] );
				heapifyUp( pos[left] );
			}
		}
		else
		{
			heap[ pos[u] ] = heap[ heapSize ];
			pos[ heap[ pos[u] ].from ] = pos[ u ];
			heapSize --;

			if( pos[ u ] <= heapSize )
			{
				heapifyUp ( pos[u] );
				heapifyDown ( pos[u] );	
			}
		}
		
		if( left > 0 )
		{
			heap[ pos[left] ].key = abs( list[ right ] - list[ left ] );
			heapifyUp( pos[left] );
			heapifyDown( pos[left] );
		}

		next[left] = right; prev[right] = left;
	}

	void	heapifyUp(int u)
	{
		while( u > 1 && heapSmaller(u , u / 2) )
		{
			heapSwap( u , u / 2 );
			u /= 2;
		}
	}

	void	heapifyDown(int u)
	{
		int		min = u;
		int		left = u * 2;
		int		right = u * 2 + 1;

		if( left <= heapSize && heapSmaller(left , min) ) min = left;
		if( right <= heapSize && heapSmaller(right , min) ) min = right;
		
		if( min != u )
		{
			heapSwap(u , min);
			heapifyDown( min );
		}
	}

	inline	bool	heapSmaller(int a, int b)
	{
		return heap[ a ].key < heap[ b ].key;
	}

	inline	void	heapSwap(int a , int b)
	{
		TheapDat	tmp;
		tmp = heap[a]; heap[a] = heap[b]; heap[b] = tmp;
		pos[ heap[a].from ] = a;
		pos[ heap[b].from ] = b;
	}

	void	printList()
	{
		int		k = next[0];

		printf(" (%d : %d)  " , heap[1].key , heapSize);
		while( k <= n )
		{
			printf("%d " , list [k]); k = next[k];
		}
		putchar('\n');
	}
}			gap , sortGap;

void	init()
{
	int		i;
	char		command	[100];

	sortN = 0; extend[0] = 0;

	scanf("%d%d" , &n , &m);
	for(i = 1; i <= n; i ++)
	{
		scanf("%d" , orig + i);
		extend[i] = 1;

		sortN ++;
		sortSeq[ sortN ].key = orig[i];
		sortSeq[ sortN ].from = 0;
	}
	extend[n + 1] = 1;

	for(i = 1; i <= m; i ++)
	{
		scanf("%s" , command);
		if( command[0] == 'I' )
		{
			query[i].type = 0;
			scanf("%d%d" , &query[i].i , &query[i].k);
			extend[ query[i].i ] ++;

			sortN ++;
			sortSeq[ sortN ].key = query[i].k;
			sortSeq[ sortN ].from = i;
		}
		else if( command[4] == 'G' )		// MIN_GAP
			query[i].type = 1;
		else	query[i].type = 2;
	}
}

void	process()
{
	int		i;

	for(i = 2; i <= n + 1; i ++)
		extend[i] += extend[i - 1];
	memcpy(final , extend , sizeof(final));
	sort(sortSeq + 1 , sortSeq + 1 + sortN);

	for(i = 1; i <= sortN; i ++)
	{
		sortGap.list[i] = sortSeq[i].key;
		if( sortSeq[i].from ) query[ sortSeq[i].from ].pos = i;
	}
	for(i = m; i > 0; i --)
		if( query[i].type == 0 )		// INSERT
			gap.list[ extend[ query[i].i ] -- ] = query[i].k;
	for(i = 1; i <= n; i ++)
		gap.list[ extend[i] ] = orig[ i ];

	n = sortN;
	gap.init();

	sortGap.init();
}

void	solve()
{
	int		i;

	for(i = m; i > 0; i --)
	{
		if( query[i].type == 1 )
			query[i].resp = gap.getMin();
		else if( query[i].type == 2 )
			query[i].resp = sortGap.getMin();
		else
		{
			gap.kick( final[ query[i].i ] -- );
			sortGap.kick( query[i].pos );

	//		printf("Gap : "); gap.printList();
	//		printf("SortGap : "); sortGap.printList();
	//		puts("========");
		}
	}
}

void	output()
{
	int		i;

	for(i = 1; i <= m; i ++)
		if( query[i].type != 0 )
			printf("%d\n" , query[i].resp);
}

int	main()
{
	freopen("form.in" , "r" , stdin);
	freopen("form.out" , "w" , stdout);

	init();
	process();
	solve();
	output();

	return 0;
}
