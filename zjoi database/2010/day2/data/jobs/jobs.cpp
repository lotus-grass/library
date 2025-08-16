#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int INF = 1000000000;
const int MAXN = 20;
const int MAXL = 3;

vector<PII> T[2];
int S[2], w[2][MAXN], tw[2][MAXN], tso[2][MAXN];
int N, cnt, t, tx, twait, countt;
int tmin[MAXN][MAXN];

void solve(int step) {
	int x, i, j, t1, t2, i1, j1, best, i11, t11, ok;

	if (step > S[0]) {
		for (i = 0; i <= S[0]; ++i)
			for (j = 0; j <= S[1]; ++j)
				tmin[i][j] = INF;

		tmin[0][0] = 0;

		for (i = 0; i < S[0]; ++i)
			for (j = 0; j < S[1]; ++j)
				if (tmin[i][j] < INF) {
					t1 = t2 = 0;
					i1 = i + 1;
					j1 = j + 1;

					while (i1 <= S[0] && j1 <= S[1]) {
						best = -1;

						for (x = 0; x < cnt; ++x) {
							ok = 1;

							for (i11 = i1, t11 = t1; t11 < t2 + T[1][x].first && i11 <= S[0]; ++i11) {
								if (T[1][x].second == w[0][i11]) {
									ok = 0;

									if (tmin[i][j] + t11 + tw[0][i11] < tmin[i11][j1 - 1])
										tmin[i11][j1 - 1] = tmin[i][j] + t11 + tw[0][i11];

									if (tmin[i][j] + 2 * (t2 + T[1][x].first) - t11 < tmin[i11 - 1][j1])
										tmin[i11 - 1][j1] = tmin[i][j] + 2 * (t2 + T[1][x].first) - t11;

									break;
								}

								t11 += tw[0][i11];
							}

							if (best == -1 && ok)
								best = x;
						}

						if (best == -1)
							break;

						x = best;

						t2 += T[1][x].first;
						++j1;

						while (i1 <= S[0] && t1 + tw[0][i1] <= t2) {
							t1 += tw[0][i1];
							++i1;
						}
					}

					if (i1 > S[0]) {
						if (tmin[i][j] + t2 < tmin[S[0]][j1 - 1])
								tmin[S[0]][j1 - 1] = tmin[i][j] + t2;
					}
					else if (j1 > S[1]) {
						if (tmin[i][j] + t2 < tmin[S[0]][j1 - 1])
								tmin[S[0]][j1 - 1] = tmin[i][j] + t2;
					}
				}
				
		for (i = 0; i < S[0]; ++i)
			if (tmin[i][S[1]] < tmin[S[0]][S[1]])
				tmin[S[0]][S[1]] = tmin[i][S[1]];
				
		for (j = 0; j < S[1]; ++j)
			if (tmin[S[0]][j] + (S[1] - j) * T[1][0].first < tmin[S[0]][S[1]])
				tmin[S[0]][S[1]] = tmin[S[0]][j] + (S[1] - j) * T[1][0].first;

		if (tx + tmin[S[0]][S[1]] < t) {
			t = tx + tmin[S[0]][S[1]];
			twait = INF;

			for (i = 1; i <= S[0]; ++i)
				tso[0][i] = w[0][i];

			for (i = 1; i <= S[1]; ++i)
				tso[1][i] = -1;
		}
	}
	else
		for (x = 0; x < cnt; ++x) {
			w[0][step] = T[0][x].second;
			tw[0][step] = T[0][x].first;
			tx += tw[0][step];

			if (tx + S[1] * T[1][0].first < t)
				solve(step + 1);

			tx -= tw[0][step];
		}
}

int main() {
	freopen("jobs.in", "r", stdin);
	freopen("jobs.out", "w", stdout);

	int cases;
	for (scanf("%d", &cases); cases--; ) {
		scanf("%d %d %d", &N, &S[0], &S[1]);

		T[0].clear();
		T[1].clear();

		for (int k = 1; k <= N; ++k) {
			int i, j;
			scanf("%d %d", &i, &j);

			T[0].push_back(make_pair(i, k));
			T[1].push_back(make_pair(j, k));
		}

		sort(T[0].begin(), T[0].end());
		sort(T[1].begin(), T[1].end());

		if (T[0][0].second != T[1][0].second) {
			printf("%d\n", S[0] * T[0][0].first + S[1] * T[1][0].first);
		}
		else {
			if (N == 1)	
				cnt = 1;
			else if (T[0][1].second != T[1][1].second)
				cnt = 2;
			else if (N == 3)
				cnt = 3;
			else if (N > 3 && T[0][2].second != T[1][2].second)
				cnt = 3;
			else
				cnt = (N > MAXL) ? MAXL : N;

			t = INF;

			if (N > 1) {
				t = S[0] * T[0][0].first + S[1] * T[1][1].first;

				for (int i = 0; i < 2; ++i)
					for (int j = 1; j <= S[i]; ++j)
						tso[i][j] = T[i][i].second;

				if (S[0] * T[0][1].first + S[1] * T[1][0].first < t) {
					t = S[0] * T[0][1].first + S[1] * T[1][0].first;
				
					for (int i = 0; i < 2; ++i)
						for (int j = 1; j <= S[i]; ++j)
							tso[i][j] = T[i][1 - i].second;
				}

				twait = -1;
			}

			tx = 0;
			solve(1);

			printf("%d\n", t);
		}
	}

	return 0;
}

