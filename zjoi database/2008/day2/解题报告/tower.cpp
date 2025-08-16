#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const	double		eps		= 1e-4;
const	int		limitSize	= 300 + 10;

struct			Tpoint
{
	double	x , y;
	
	Tpoint(){}
	Tpoint(double x0 , double y0) : x(x0), y(y0) {}
};

inline	int	sgn(double x)
{
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : +1;
}

Tpoint	operator - (const Tpoint& A , const Tpoint& B)
{
	return Tpoint(A.x - B.x , A.y - B.y);
}

inline	int	crossProduct(const Tpoint& p0 , const Tpoint& p1 , const Tpoint& p2)
{
	return	sgn( (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x) );
}

inline	int	crossProduct(const Tpoint& A , const Tpoint& B)
{
	return	sgn( A.x * B.y - A.y * B.x );
}

inline	bool	segmentCross(const Tpoint& A , const Tpoint& B , const Tpoint& P , const Tpoint& Q)
{
	return	crossProduct(A,B,P) * crossProduct(A,B,Q) < 0 && crossProduct(P,Q,A) * crossProduct(P,Q,B) < 0;
}

inline	Tpoint	crossPoint(const Tpoint& A , const Tpoint& B , const Tpoint& P , const Tpoint& Q)
{
	double t = ((A.x - P.x) * (B.y - A.y) - (A.y - P.y) * (B.x - A.x))
			  / ((Q.x - P.x) * (B.y - A.y) - (Q.y - P.y) * (B.x - A.x));
	return	Tpoint( P.x + (Q.x - P.x) * t , P.y + (Q.y - P.y) * t );
}

int			n;
Tpoint			list	[limitSize];
double			ret;

void	trySolution(const Tpoint& V)
{
	if (V.x < list[0].x || V.x > list[n - 1].x) return;

	int		i;
	for (i = 1; i < n; i ++)
		if (list[i].x >= V.x - eps) break;

	double		level = list[i - 1].y + (list[i].y - list[i - 1].y) / (list[i].x - list[i - 1].x) * (V.x - list[i - 1].x);

	if (level > V.y + eps) return;
	if (V.y - level > ret) return;

	int		p;
	for (p = i; p + 1 < n; p ++)
		if (crossProduct(V , list[p] , list[p + 1]) < 0)
		{
			return;
		}
	for (p = i - 1; p - 1 >= 0; p --)
		if (crossProduct(V , list[p] , list[p - 1]) > 0)
		{
			return;
		}
	ret = V.y - level;
}

void	solve()
{
	ret = 1e20;

	int		i , j;
	for (i = 0; i + 1 < n; i ++)
		for (j = i + 1; j + 1 < n; j ++)
		{
			if ( crossProduct(list[i + 1] - list[i] , list[j + 1] - list[j]) )
			{
				trySolution( crossPoint(list[i] , list[i + 1] , list[j] , list[j + 1]) );
			}
		}
	
	for (i = 0; i + 1 < n; i ++)
		for (j = 0; j < n; j ++)
		{
			trySolution( Tpoint(list[j].x , 
				list[i].y + (list[i + 1].y - list[i].y) / (list[i + 1].x - list[i].x) * (list[j].x - list[i].x)	) );
		}
}

int		X	[limitSize];
int		Y	[limitSize];

int	main()
{
	freopen("tower.in" , "r" , stdin);
	freopen("tower.out" , "w" , stdout);

	scanf("%d" , &n);
	for (int i = 0; i < n; i ++)
		scanf("%d" , X + i);
	for (int i = 0; i < n; i ++)
		scanf("%d" , Y + i);
	for (int i = 0; i < n; i ++)
		list[i] = Tpoint(X[i] , Y[i]);

	solve();

	printf("%.3lf\n" , ret);

	return	0;
}
