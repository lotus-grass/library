/*
 * ZJOI 2010 Day 1 Problem 1
 *
 * Author: Dong Zhou
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long llint;

llint A, B;
llint p10[20];

llint solve( llint n, llint k )
{
	int nD = 0;
	int D[30];
	llint suffix[30];
	
	for( llint nn = n; nn; nn /= 10 ) 
		D[nD++] = nn%10;
	reverse( D, D+nD );

//	printf( "nD = %d\n", nD );
//	for( int i = 0; i < nD; ++i ) printf( "%d", D[i] );
//	putchar( '\n' );

	suffix[nD] = 0;
	for( int i = nD-1; i >= 0; --i )
		suffix[i] = D[i]*p10[nD-i-1] + suffix[i+1];

	llint answer = 0;
	llint prefix = 0;

	for( int len = 1; len < nD; ++len )
		for( int i = (k==0 ? 1 : 0); i < len; ++i ) {
			llint zz = p10[len-i-1];
			if( i ) zz *= 9*p10[i-1];

			answer += zz;
		}

	for( int i = 0; i < nD; prefix = prefix*10 + D[i++] ) {
		if( i==0 && k==0 ) continue;
	
		llint base = (i==0 ? 0 : p10[i-1]);

		answer += (prefix-base) * p10[nD-i-1];
		if( k < D[i] ) 
			answer += p10[nD-i-1];
		else if( k == D[i] )
			answer += suffix[i+1]+1;
	}
	
	return answer;
}

int main( void )
{
//	freopen( "count.in", "r", stdin );
//	freopen( "count.out", "w", stdout );
	
	p10[0] = 1;
	for( int i = 1; i < 15; ++i ) p10[i] = p10[i-1]*10;
	
	scanf( "%lld %lld", &A, &B );
	
	for( int i = 0; i < 10; ++i ) {
		if( i > 0 ) putchar( ' ' );
		printf( "%lld", solve(B, i)-solve(A-1, i) );
//		printf( "%lld %lld\n", solve(A-1, i), solve(B, i) );
	}
//	printf( "%lld\n", solve(10, 0) );
	putchar( '\n' );
	
	return 0;
}

