// 2005-3-10
// by Jingyue Wu

#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

const int MAX_N = 100;
const int MAX_N_CROC = 100;
const int MAX_T = 12; // LCM of 2, 3, 4
const int MAX_N_BIN = 100;
const int MODULE = 10000;

struct Crocodile {
	int T;
	int path[MAX_T];
};
typedef int Matrix[MAX_N][MAX_N];

bool g[MAX_N][MAX_N];
Crocodile croc[MAX_N_CROC];
int bin[MAX_N_BIN];
Matrix a, b;
int n, m, u, v, nStep, nCroc, nBin;

void inputData() {
	ifstream fin("swamp.in");
	int i, j, x, y;
	fin >> n >> m >> u >> v >> nStep;
	memset(g, 0, sizeof(g));
	for (i = 0; i < m; i++) {
		fin >> x >> y;
		g[x][y] = true; g[y][x] = true;
	}
	fin >> nCroc;
	for (i = 0; i < nCroc; i++) {
		fin >> croc[i].T;
		for (j = 0; j < croc[i].T; j++) fin >> croc[i].path[j];
		for (j = croc[i].T; j < MAX_T; j++) croc[i].path[j] = croc[i].path[j - croc[i].T];
	}
}

void multiply(Matrix& a, Matrix& b) {
	Matrix c;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			c[x][y] = 0;
			for (int z = 0; z < n; z++) c[x][y] = (c[x][y] + a[x][z] * b[z][y]) % MODULE;
		}
	}
	memcpy(a, c, sizeof(Matrix));
}

void oneStep(Matrix &a, int step) {
	Matrix a1;
	bool forbid[MAX_N];
	int i, x, y, z;
	step %= MAX_T;
	memset(forbid, 0, sizeof(forbid));
	for (i = 0; i < nCroc; i++) forbid[croc[i].path[step]] = true;
	memset(a1, 0, sizeof(a1));
	for (y = 0; y < n; y++) {
		if (!forbid[y]) {
			for (x = 0; x < n; x++) {
				for (z = 0; z < n; z++) {
					if (g[z][y]) {
						a1[x][y] = (a1[x][y] + a[x][z]) % MODULE;
					}
				}
			}
		}
	}
	memcpy(a, a1, sizeof(Matrix));
}

void print(Matrix& a) {
	int x, y;
	for (x = 0; x < n; x++) {
		for (y = 0; y < n; y++) cout << a[x][y] << ' ';
		cout << endl;
	}
	cout << endl;
}

void solve() {
	int step, i, k, r, x;
	// get matrix of one cycle
	memset(a, 0, sizeof(a));
	for (x = 0; x < n; x++) a[x][x] = 1;
	for (step = 1; step <= MAX_T; step++) oneStep(a, step);
//	print(a);
	// get a ^ (nStep / T)
	k = nStep / MAX_T;
	nBin = 0;
	while (k > 0) {
		bin[nBin] = k % 2;
		k /= 2;
		nBin++;
	}
	memset(b, 0, sizeof(b));
	for (x = 0; x < n; x++) b[x][x] = 1;
	for (i = nBin - 1; i >= 0; i--) {
		multiply(b, b);
		if (bin[i] == 1) multiply(b, a);
	}
//	print(b);
	// multiply by remainder matrix
	r = nStep % MAX_T;
//	cout << "r = " << r << endl << endl;
	for (step = 1; step <= r; step++) oneStep(b, step);
//	print(b);
}

void outputData() {
	ofstream fout("swamp.out");
	fout << b[u][v] << endl;
}

int main() {
	inputData();
	solve();
	outputData();
	return 0;
}
