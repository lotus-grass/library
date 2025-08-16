// 2004-3-20
// bu Jingyue Wu

// usage:
// swamp_gen n m nStep nCroc fileName

#include <fstream>
#include <ctime>
#include <cstdlib>
#include <memory>
using namespace std;

const int MAX_N = 50;
const int MAX_T = 4;

bool g[MAX_N][MAX_N];
int n, m, nStep, nCroc, u, v;

int main(int argc, char* argv[]) {
	int path[MAX_T];
	int i, j, x, y, T;
	n = atoi(argv[1]); m = atoi(argv[2]); nStep = atoi(argv[3]); nCroc = atoi(argv[4]);
	ofstream fout(argv[5]);
	srand((unsigned int)time(NULL));
	do {
		u = rand() % n; v = rand() % n;
	}
	while (u == v);
	fout << n << ' ' << m << ' ' << u << ' ' << v << ' ' << nStep << endl;
	memset(g, 0, sizeof(g));
	for (i = 0; i < m; i++) {
		do {
			x = rand() % n; y = rand() % n;
		}
		while (x == y || g[x][y]);
		g[x][y] = true; g[y][x] = true;
		fout << x << ' ' << y << endl;
	}
	fout << nCroc << endl;
	for (i = 0; i < nCroc; i++) {
		T = rand() % 3 + 2;
		fout << T;
		do {
			path[0] = rand() % n;
		}
		while (path[0] == u);
		for (j = 1; j < T; j++) {
			do {
				path[j] = rand() % n;
			}
			while (path[j] == path[j - 1]);
		}
		for (j = 0; j < T; j++) fout << ' ' << path[j];
		fout << endl;
	}
	return 0;
}
