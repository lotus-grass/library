// 2005-3-10
// by Jingyue Wu

#include <fstream>
#include <memory>
using namespace std;

const int MAX_N = 100;
const int MAX_N_CROC = 100;
const int MAX_T = 10;
const int MODULE = 10000;

struct Crocodile {
	int T;
	int path[MAX_T];
};

bool a[MAX_N][MAX_N], forbid[MAX_N];
Crocodile croc[MAX_N_CROC];
int num[MAX_N], num1[MAX_N], cur[MAX_N_CROC];
int n, m, u, v, nStep, nCroc;

void inputData() {
	ifstream fin("swamp.in");
	int i, j, x, y;
	fin >> n >> m >> u >> v >> nStep;
	memset(a, 0, sizeof(a));
	for (i = 0; i < m; i++) {
		fin >> x >> y;
		a[x][y] = true; a[y][x] = true;
	}
	fin >> nCroc;
	for (i = 0; i < nCroc; i++) {
		fin >> croc[i].T;
		for (j = 0; j < croc[i].T; j++) fin >> croc[i].path[j];
	}
}

void solve() {
	int step, i, x, y;
	memset(cur, 0, sizeof(cur));
	memset(num, 0, sizeof(num)); num[u] = 1;
	for (step = 0; step < nStep; step++) {
		memset(num1, 0, sizeof(num1));
		memset(forbid, 0, sizeof(forbid));
		for (i = 0; i < nCroc; i++) {
			cur[i] = (cur[i] + 1) % croc[i].T;
			forbid[croc[i].path[cur[i]]] = true;
		}
		for (x = 0; x < n; x++) {
			for (y = 0; y < n; y++) {
				if (a[x][y] && !forbid[y]) num1[y] = (num1[y] + num[x]) % MODULE;
			}
		}
		memcpy(num, num1, sizeof(num));
	}
}

void outputData() {
	ofstream fout("swamp.ans");
	fout << num[v] << endl;
}

int main() {
	inputData();
	solve();
	outputData();
	return 0;
}
