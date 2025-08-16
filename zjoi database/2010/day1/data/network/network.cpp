/*
 * ZJOI 2010 Day 1 Problem 2
 *
 * Author: Dong Zhou
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>

struct edge {
	int a, b, c, w;
};

int n, m, K;
int source, sink;
edge edges[100005];

int head[1005];
int endpoint[400005], C[400005], W[400005], next[400005];
int ep;

int queue[1000005];
int front, back;
int trace[1005], dad[1005];

int extendC( void )
{
	front = back = 0;
	memset(dad, -1, sizeof(dad));

	queue[back++] = source;
	dad[source] = source;

	for( ; front < back; ++front ) {
		int x = queue[front];

		for( int z = head[x]; z >= 0; z = next[z] ) if( C[z] > 0 ) {
			int y = endpoint[z];

			if( dad[y] < 0 ) {
				queue[back++] = y;
				trace[y] = z, dad[y] = x;
			}
		}
	}

	if( dad[sink] < 0 ) return 0;

	int zz = 1000000000;

	for( int x = sink; x != source; x = dad[x] ) zz = (zz < C[trace[x]]) ? zz : C[trace[x]];
	for( int x = sink; x != source; x = dad[x] ) {
		C[trace[x]] -= zz;
		C[trace[x]^1] += zz;
	}

	return zz;
}

int wm[1005];
bool used[1005];

void push( int x, int w, int _trace )
{
	if( wm[x] < 0 || w < wm[x] ) {
		trace[x] = _trace;
		wm[x] = w;
		if( !used[x] ) {
			queue[back++] = x;
			used[x] = true;
		}
	}
}

int extendW( void )
{
	front = back = 0;
	memset(wm, -1, sizeof(wm));
	memset(used, false, sizeof(used));

	for( push(source, 0, -1); front < back; ++front ) {
		int x = queue[front]; used[x] = false;

		for( int z = head[x]; z >= 0; z = next[z] ) if( C[z] > 0 )
			push(endpoint[z], wm[x]+W[z], z);
	}

	for( int x = sink; x != source; x = endpoint[trace[x]^1] ) {
		--C[trace[x]];
		++C[trace[x]^1];
	}

	return wm[sink];
}

void addedge( int a, int b, int c, int w )
{
	endpoint[ep] = b, C[ep] = c, W[ep] =  w, next[ep] = head[a]; head[a] = ep++;
	endpoint[ep] = a, C[ep] = 0, W[ep] = -w, next[ep] = head[b]; head[b] = ep++;
}

int main( void )
{
	freopen( "network.in", "r", stdin );
	freopen( "network.out", "w", stdout );

	scanf( "%d%d%d", &n, &m, &K );
	source = 0, sink = n - 1;
	for( int i = 0; i < m; ++i ) {
		int a, b, c, w; scanf( "%d%d%d%d", &a, &b, &c, &w ); --a, --b;
		edges[i] = (edge) { a, b, c, w };
	}

	memset( head, -1, sizeof(head) );
	for( int i = 0; i < m; ++i ) addedge( edges[i].a, edges[i].b, edges[i].c, 0 );

	int answerC = 0, answerW = 0;
	int zz;

	while( (zz = extendC()) > 0 )
		answerC += zz;

	for( int i = 0; i < m; ++i ) addedge( edges[i].a, edges[i].b, K, edges[i].w );
	while( K-- )
		answerW += extendW();

	printf( "%d %d\n", answerC, answerW );

	return 0;
}

