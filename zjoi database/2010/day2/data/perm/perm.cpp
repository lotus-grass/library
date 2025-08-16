#include <cstdio>
#include <cstring>

typedef long long llint;

int n, p;
llint F[1000005];
llint ways[1000005];

llint extended_gcd( llint a, llint &x, llint b, llint &y )
{
	if( b == 0 ) {
		x = 1;
		y = 0;
		return a;
	}

	/*
	 * b * y' + (a - (a/b) * b) * x' == d
	 * x = x'
	 * y = y' - (a / b) * x'
	 */

	llint d = extended_gcd(b, y, a%b, x);
	y -= (a/b) * x;

	return d;
}

llint inv( llint x )
{
	llint y;
	llint q;
	llint d = extended_gcd(x, y, p, q);

	return (y%p + p) % p;
}

llint binom( int n, int m )
{
	llint ret = F[n];

	ret = (ret*inv(F[m])) % p;
	ret = (ret*inv(F[n-m])) % p;

	return ret;
}

llint Ways( int n )
{
	llint &ret = ways[n];
	if( ret >= 0 ) return ret;

	int sz = 1;
	while( sz*2 + 1 <= n )
		sz = sz*2 + 1;

	int l;
	int r;
	if( sz + (sz+1)/2 >= n ) {
		r = sz/2;
		l = n-1 - r;
	} else {
		l = sz/2 + (sz+1)/2;
		r = n-1 - l;
	}

	ret = binom(n-1, l);
	ret = (ret*Ways(l)) % p;
	ret = (ret*Ways(r)) % p;

	return ret;
}

int main( void )
{
	freopen( "perm.in", "r", stdin );
//	freopen( "perm.out", "w", stdout );

	scanf( "%d %d", &n, &p );

	*F = 1;
	for( int i = 1; i <= n; ++i )
		F[i] = (F[i-1]*i) % p;

	memset(ways, -1, sizeof(ways));
	ways[0] = ways[1] = 1;

	printf( "%lld\n", Ways(n) );

	return 0;
}

