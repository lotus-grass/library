/*
Program		:	Score
Author		:	Chen Mingcheng
*/

#include <cstdio>

const int maxn = 100;

bool used[maxn][4];
int opt[2][4][4][4][4];

void Init() {
	freopen("score.in", "r", stdin);
	freopen("score.out", "w", stdout);
	int i, j, n;
	char ch;
	for (i = 0; i < maxn; i++)
		for (j = 0; j < 4; j++)
			used[i][j] = 0;
	scanf("%d", &n);
	while (n--) {
		scanf("%d%c", &i, &ch);
		i--;
		switch (ch) {
			case 'y' : used[i][0] = 1; break;
			case 'r' : used[i][1] = 1; break;
			case 'g' : used[i][2] = 1; break;
			case 'b' : used[i][3] = 1; break;
		}
	}
}

inline void Update(int &a, int b) {
	if (a < b) a = b;
}

inline int Min(int a, int b) {
	return a < b ? a : b;
}

void Work() {
	int curr = 0, prev = 0, t, i, j, k, l, temp, tt, ans = -0x7fffffff;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 4; k++)
				for (l = 0; l < 4; l++)
					opt[0][i][j][k][l] = i + j + k + l ? -1 : 0;
	for (t = 0; t < maxn; t++) {
		curr = 1 - prev;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				for (k = 0; k < 4; k++)
					for (l = 0; l < 4; l++)
						opt[curr][i][j][k][l] = -1;
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				for (k = 0; k < 4; k++)
					for (l = 0; l < 4; l++)
						if ((temp = opt[prev][i][j][k][l]) != -1) {
							if (used[t][0] + used[t][1] + used[t][2] + used[t][3] == 4) {
								tt = temp + (t + 1) * 3;
								if (i == 2) tt += 3 * t;
								if (i == 3) tt += t + 1;
								Update(opt[curr][Min(i + 1, 3)][0][0][0], tt);
								tt = temp + (t + 1) * 3;
								if (j == 2) tt += 3 * t;
								if (j == 3) tt += t + 1;
								Update(opt[curr][0][Min(j + 1, 3)][0][0], tt);
								tt = temp + (t + 1) * 3;
								if (k == 2) tt += 3 * t;
								if (k == 3) tt += t + 1;
								Update(opt[curr][0][0][Min(k + 1, 3)][0], tt);
								tt = temp + (t + 1) * 3;
								if (l == 2) tt += 3 * t;
								if (l == 3) tt += t + 1;
								Update(opt[curr][0][0][0][Min(l + 1, 3)], tt);
								Update(opt[curr][0][0][0][0], temp + (t + 1) * 4);
							}
							if (used[t][0] + used[t][1] + used[t][2] + used[t][3] == 3) {
								tt = temp + (t + 1) * 3;
								Update(opt[curr][0][0][0][0], tt);
							}
							tt = temp;
							if (used[t][0]) {
								if (i == 2) tt += 3 * t;
								if (i == 3) tt += t + 1;
							}
							if (used[t][1]) {
								if (j == 2) tt += 3 * t;
								if (j == 3) tt += t + 1;
							}
							if (used[t][2]) {
								if (k == 2) tt += 3 * t;
								if (k == 3) tt += t + 1;
							}
							if (used[t][3]) {
								if (l == 2) tt += 3 * t;
								if (l == 3) tt += t + 1;
							}
							Update(opt[curr][Min(i + 1, 3) * used[t][0]][Min(j + 1, 3) * used[t][1]][Min(k + 1, 3) * used[t][2]][Min(l + 1, 3) * used[t][3]], tt);
						}
		prev = curr;
	}
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 4; k++)
				for (l = 0; l < 4; l++)
					Update(ans, opt[curr][i][j][k][l]);
	printf("%d\n", ans);
}

int main() {
	Init();
	Work();
	return 0;
}
