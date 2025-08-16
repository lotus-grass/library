// 2005-3-20
// by Jingyue Wu

#include <fstream>
#include <queue>
using namespace std;

const int MAX_N_STATE = 362880;
const int TARGET_CODE = 0;

typedef int Board[3][3];

ifstream fin("num9.in");
ofstream fout("num9.out");

queue<int> q;
Board originBoard;
int prev[MAX_N_STATE], step[MAX_N_STATE], fact[3][3];
int originCode;

void inputData() {
	int x, y;
	fact[2][2] = 1; fact[2][1] = 1; fact[2][0] = 2;
	fact[1][2] = 6; fact[1][1] = 24; fact[1][0] = 120;
	fact[0][2] = 720; fact[0][1] = 5040; fact[0][0] = 40320;
	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) fin >> originBoard[x][y];
	}
}

int toCode(Board& board) {
	bool used[9];
	int ans, x , y, k, i;
	memset(used, 0, sizeof(used));
	ans = 0;
	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) {
			k = board[x][y];
			for (i = 0; i < k; i++) {
				if (!used[i]) ans += fact[x][y];
			}
			used[k] = true;
		}
	}
	return ans;
}

void toBoard(int code, Board& board) {
	bool used[9];
	int x, y, d, i;
	memset(used, 0, sizeof(used));
	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) {
			d = code / fact[x][y];
			i = 0; while (used[i]) i++;
			while (d > 0) {
				i++; while (used[i]) i++;
				d--;
			}
			board[x][y] = i; used[i] = true;
			code %= fact[x][y];
		}
	}
}

void shift(Board& board) {
	int temp;
	temp = board[1][0]; board[1][0] = board[1][2]; board[1][2] = board[1][1]; board[1][1] = temp;
}

void shiftBack(Board& board) {
	int temp;
	temp = board[1][0]; board[1][0] = board[1][1]; board[1][1] = board[1][2]; board[1][2] = temp;
}

void rotate(Board& board) {
	int temp;
	temp = board[0][0]; board[0][0] = board[1][0]; board[1][0] = board[2][0];
	board[2][0] = board[2][1]; board[2][1] = board[2][2]; board[2][2] = board[1][2];
	board[1][2] = board[0][2]; board[0][2] = board[0][1]; board[0][1] = temp;
}

void solve() {
	Board currentBoard;
	int currentCode, newCode;
	memset(prev, -1, sizeof(prev));
	memset(step, -1, sizeof(step));
	originCode = toCode(originBoard); q.push(originCode); prev[originCode] = originCode; step[originCode] = 0;
	while (!q.empty()) {
		currentCode = q.front(); toBoard(currentCode, currentBoard);
		// shift
		shift(currentBoard); newCode = toCode(currentBoard);
		if (prev[newCode] == -1) {
			q.push(newCode); prev[newCode] = currentCode; step[newCode] = step[currentCode] + 1;
			if (newCode == TARGET_CODE) break;
		}
		shiftBack(currentBoard);
		// rotate
		rotate(currentBoard); newCode = toCode(currentBoard);
		if (prev[newCode] == -1) {
			q.push(newCode); prev[newCode] = currentCode; step[newCode] = step[currentCode] + 1;
			if (newCode == TARGET_CODE) break;
		}
		q.pop();
	}
}

void print(int code) {
	Board board;
	if (prev[code] != code) print(prev[code]);
	toBoard(code, board);
	fout << board[0][0] << ' ' << board[0][1] << ' ' << board[0][2] << endl;
	fout << board[1][0] << ' ' << board[1][1] << ' ' << board[1][2] << endl;
	fout << board[2][0] << ' ' << board[2][1] << ' ' << board[2][2] << endl;
	fout << endl;
}

void outputData() {
	if (prev[TARGET_CODE] == -1) fout << "UNSOLVABLE" << endl;
	else {
		fout << step[TARGET_CODE] << endl;
		print(TARGET_CODE);
	}
}

int main() {
	inputData();
	solve();
	outputData();
	return 0;
}
