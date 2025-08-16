/*
 *	Problem		:	Movement, ZJOI 2008
 *	Date		:	2008-3-17
 *	Algorithm	:	string algorithm
 *	Author		:	
 *
 */

#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const	double	eps = 1e-9;
const	double	PI = 3.1415926535897932384626433832795;
const	int	maxN = 200000;
const	int	maxM = 200000;

struct	SegType
{
	double	times;
	double	angle;

	bool operator==(const SegType &B)
	{
		return abs(times - B.times) < eps && abs(angle - B.angle) < eps;
	}

	bool operator!=(const SegType &B)
	{
		return !(*this == B);
	}

	bool operator<(const SegType &B)
	{
		return times < B.times - eps || times < B.times + eps && angle < B.angle - eps;
	}
};

SegType		*seg[maxM];
int		len[maxM];
int		N, M;

void	readIn(int k)
{
	static int x[maxN], y[maxN];

	if (k < M)
		scanf("%d", &len[k]);
	else
		len[k] = N;

	seg[k] = new SegType[len[k]];
	SegType *track = seg[k];

	for (int i = 0; i < len[k]; ++i) 
		scanf("%d%d", &x[i], &y[i]);

	for (int i = 0; i < len[k] - 1; ++i) 
		track[i].times = hypot(x[i + 1] - x[i], y[i + 1] - y[i]), track[i].angle = atan2((double)x[i + 1] - x[i], (double)y[i + 1] - y[i]);

//	cout << len[k] << endl;
//	for (int i = 0; i < len[k] - 1; ++i) cout << track[i].times << ' ' << track[i].angle << endl;

	for (int i = 0; i < len[k] - 2; ++i)
	{
		track[i].times /= track[i + 1].times, track[i].angle -= track[i + 1].angle;
		while (track[i].angle <= -PI) track[i].angle += PI;
		while (track[i].angle > PI) track[i].angle -= PI;
	}

	len[k] -= 2;
}

int	count(SegType *A, SegType *B, int N, int M)
{
	if (!N) return M + 1;

	static int pre[maxN];
	pre[1] = 0;
	for (int i = 2; i <= N; ++i)
	{
		int j = pre[i - 1];
		while (j && A[j] != A[i - 1]) j = pre[j];
		pre[i] = A[j] == A[i - 1] ? j + 1 : j;
	}

	int L = 0, ret = 0;
	for (int i = 0; i < M; ++i)
	{
		while (L && (L == N || A[L] != B[i])) L = pre[L];
		L = A[L] == B[i] ? L + 1 : L;
		if (L == N) ++ret;
	}
	return ret;
}

int	main()
{
	freopen("movement.in" , "r" , stdin);
	freopen("movement.out" , "w" , stdout);

	scanf("%d%d", &N, &M);

	for (int i = 0; i <= M; ++i) readIn(i);

	static SegType pattern[maxN];

	N -= 2;

	for (int i = 0; i < M; ++i)
	{ 
	 	bool UD_same = 1, LR_same = 1, DI_same = 1;
	 	for (int j = 0; j < len[i]; ++j)
	 	{
	 		if (abs(seg[i][j].angle + seg[i][len[i] - j - 1].angle) > eps || abs(1 / seg[i][j].times - seg[i][len[i] - j - 1].times) > eps) LR_same = 0;
	 		if (abs(seg[i][j].angle) > eps) UD_same = 0;
	 		if (abs(seg[i][j].times - 1 / seg[i][len[i] - j - 1].times) > eps) DI_same = 0;
	 	}

//		cout << i << ' ' << UD_same << ' ' << LR_same << ' ' << DI_same << endl;

 		int cnt = 0;
 		cnt += count(seg[i], seg[M], len[i], N);
 		if (!UD_same)
 		{
 			for (int j = 0; j < len[i]; ++j) 
 				pattern[j].angle = - seg[i][j].angle, pattern[j].times = seg[i][j].times;
 			cnt += count(pattern, seg[M], len[i], N);
 		}
 		if (!LR_same && !DI_same)
 		{
 			for (int j = 0; j < len[i]; ++j) 
 				pattern[j].angle = - seg[i][len[i] - j - 1].angle, pattern[j].times = 1 / seg[i][len[i] - j - 1].times;
			cnt += count(pattern, seg[M], len[i], N);
		}
		if (!UD_same && !LR_same && !DI_same)
		{
			for (int j = 0; j < len[i]; ++j) 
				pattern[j].angle = seg[i][len[i] - j - 1].angle, pattern[j].times = 1 / seg[i][len[i] - j - 1].times;
			cnt += count(pattern, seg[M], len[i], N);
		}
		printf("%d\n", cnt);
	}

	return 0;
}
