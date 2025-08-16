/*
 * ZJOI 2010 Day 1 Problem 3
 *
 * Author: Dong Zhou
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int n, K;
int D[20005], C[20005], S[20005], W[20005];

vector<pair<int, int> > events[20005];
int opt[20005];
int tree[65536], offset[65536];

int answer;

int binarySearch( int n, int A[], int key )
{
	int l = 0, r = n - 1;

	while( l <= r ) 
	{
		int m = (l + r) / 2;
		
		if( A[m] > key ) r = m - 1; else l = m + 1;
	}

	return r + 1;
}

int query( int p, int l, int r, int nl, int nr )
{
	if( nl <= l && nr >= r ) return offset[p] + tree[p];

	int m = (l + r) / 2;
	int answer = 2000000000;

	if( nl <= m ) answer = min(answer, query(p * 2 + 1, l, m, nl, nr));
	if (nr > m ) answer = min(answer, query(p * 2 + 2, m + 1, r, nl, nr));

	return answer + offset[p];
}

void add( int p, int l, int r, int nl, int nr, int value )
{
	if( nl <= l && nr >= r ) 
	{
		offset[p] += value;
		return;
	}

	int m = (l + r) / 2;

	if( nl <= m ) 
		add( p*2 + 1, l, m, nl, nr, value );
	if( nr > m ) 
		add( p*2 + 2, m + 1, r, nl, nr, value );
	tree[p] = min(offset[p*2 + 1] + tree[p*2 + 1], offset[p*2 + 2] + tree[p*2 + 2]);
}

void checkOpt( int k )
{
	priority_queue<pair<int, int> > heap;
	int cost = 0;

	for( int i = n - 1; i >= k; --i)
	{
		while (!heap.empty() && heap.top().first > D[i])
		{
			cost += heap.top().second;
			heap.pop();
		}
		answer = min(answer, opt[i] + cost);
		heap.push(make_pair(D[i] - S[i], W[i]));
	}
}

int main()
{
	freopen( "base.in", "r", stdin );
	freopen( "base.out", "w", stdout );

	scanf( "%d %d", &n, &K );
	for( int i = 1; i < n; ++i ) scanf( "%d", &D[i] );
	for( int i = 0; i < n; ++i ) scanf( "%d", &C[i] );
	for( int i = 0; i < n; ++i ) scanf( "%d", &S[i] );
	for( int i = 0; i < n; ++i ) scanf( "%d", &W[i] );

	answer = 0;
	for( int i = 0; i < n; ++i ) answer += W[i];

	memset(tree, 0, sizeof(tree));
	memset(offset, 0, sizeof(offset));
	for( int i = 0; i < n; ++i ) 
	{
		opt[i] = C[i] + query(0, 0, n-1, i, i);

		int x = binarySearch( n, D, D[i]+S[i] );
		if( x < n ) 
		{
//			printf("i = %d, x = %d\n", i, x);
			add(0, 0, n-1, x, n-1, W[i]);
		}
	}
	checkOpt(0);

//	for (int i = 0; i < n; ++i) printf("%d ", opt[i]);
//	printf("\n");

	for( int k = 1; k < K; ++k ) 
	{
		memset(tree, 0, sizeof(tree));
		memset(offset, 0, sizeof(offset));
		for( int i = k - 1; i < n; ++i ) 
		{
			add(0, 0, n-1, i, i, opt[i]);
			events[i].clear();
		}

		for( int x = k; x < n; ++x )
		{
			while (!events[x].empty())
			{
				add(0, 0, n-1, 0, events[x].back().first, events[x].back().second);
				events[x].pop_back();
			}
//			printf("k = %d, x = %d, query = %d\n", k, x, query(0, 0, n-1, k-1, x-1));
			opt[x] = query(0, 0, n-1, k-1, x-1) + C[x];

			int i = binarySearch(n, D, D[x]+S[x]);
			int j = binarySearch(n, D, D[x]-S[x]); while( j >= 0 && D[j] >= D[x]-S[x] ) --j;
			if (j >= 0 && i < n) events[i].push_back(make_pair(j, W[x]));
		}
		checkOpt(k);
	}
	printf( "%d\n", answer );

	return 0;
}

