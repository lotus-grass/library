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
int			father	[limitSize];
double			ret;

int			queue	[limitSize] , head , tail;
int			left	[limitSize];

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

void	process()
{
	int		i , u , v , p , size;

	queue[ head = tail = 1 ] = root;
	memset(mark , 0 , sizeof(mark)); mark[root] = 1;

	while( head <= tail )
	{
		u = queue[ head ++ ];
		size = list[u].size();

		for(i = 0; i < size; i ++)
		{
			v = list[u][i].u;
			if( mark[v] ) continue;
			father[v] = u;
			queue[ ++ tail ] = v; mark[v] = 1;
		}
	}

	for(p = n; p > 0; p --)
	{
		u = queue[p]; longest[u] = 0;
		size = list[u].size();
		for(i = 0; i < size; i ++)
		{
			v = list[u][i].u;
			if( father[v] == u && longest[v] + list[u][i].cost > longest[u] )
				longest[u] = longest[v] + list[u][i].cost;
		}
	}
}

void	solve()
{	
	int		i , u , v , size;

	queue[ head = tail = 1 ] = root; left[ root ] = longest[root]; ret = 0;
	memset(mark , 0 , sizeof(mark)); mark[root] = 1;

	while( head <= tail )
	{
		u = queue[ head ++ ]; ret += left[u] - longest[u];
		size = list[u].size();

		for(i = 0; i < size; i ++)
		{
			v = list[u][i].u;
			if( mark[v] ) continue;
			left[v] = longest[u] - list[u][i].cost;
			queue[ ++ tail ] = v; mark[v] = 1;
		}
	}

	printf("%.0lf\n" , ret);
}

int	main()
{
	freopen("synch.in" , "r" , stdin);
	freopen("synch.out" , "w" , stdout);

	init();
	process();
	solve();

	return 0;
}
