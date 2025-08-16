#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const	int		limitSize	= 1000000 + 10;

struct			Tedge
{
	int		u;
	int		cost;
};

int			n , root;
vector<Tedge>		list	[limitSize];
bool			mark	[limitSize];
int			longest	[limitSize];
double			ret;

void	init()
{
	int		i;
	int		a , b , w;
	Tedge		t;

	scanf("%d%d" , &n , &root); root --;
	for(i = 1; i < n; i ++)
	{
		scanf("%d%d%d" , &a , &b , &w); a -- , b --;
		t.u = b; t.cost = w; list[a].push_back(t);
		t.u = a; t.cost = w; list[b].push_back(t);
	}
}

void	calcInfo( int u )
{
	int		p , v , size = list[u].size();

	mark[u] = 1;
	longest[u] = 0;

	for(p = 0; p < size; p ++)
	{
		v = list[u][p].u;
		if( mark[v] ) continue;
		calcInfo( v );

		if( longest[v] + list[u][p].cost > longest[u] ) 
			longest[u] = longest[v] + list[u][p].cost;
	}
}

void	expand(int u , int left)
{
	ret += left - longest[u];
	mark[u] = 1;

	int		p , v , size = list[u].size();

	for(p = 0; p < size; p ++)
	{
		v = list[u][p].u;
		if( mark[v] ) continue;		
		expand(v , longest[u] - list[u][p].cost);
	}
}

void	solve()
{
	memset(mark , 0 , sizeof(mark));

	calcInfo( root );
	ret = 0;

	memset(mark , 0 , sizeof(mark));
	expand( root , longest[root] );

	printf("%.0lf\n" , ret);
}

int	main()
{
	freopen("synch.in" , "r" , stdin);
	freopen("synch.out" , "w" , stdout);

	init();
	solve();

	return 0;
}
