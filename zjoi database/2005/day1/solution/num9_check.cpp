// 2005-3-21
// by Jingyue Wu

// Usage:
// num9_check inFile outFile ansFile

#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

typedef int Board[3][3];

Board originBoard;
Board targetBoard = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

void readBoard(istream& in, Board& board) {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) in >> board[x][y];
	}
}

bool equal(Board& a, Board& b) {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (a[x][y] != b[x][y]) return false;
		}
	}
	return true;
}

void getRotatedBoard(Board& a, Board& b) {
	b[0][0] = a[1][0]; b[0][1] = a[0][0]; b[0][2] = a[0][1];
	b[1][0] = a[2][0]; b[1][1] = a[1][1]; b[1][2] = a[0][2];
	b[2][0] = a[2][1]; b[2][1] = a[2][2]; b[2][2] = a[1][2];
}

void getShiftedBoard(Board& a, Board& b) {
	b[0][0] = a[0][0]; b[0][1] = a[0][1]; b[0][2] = a[0][2];
	b[1][0] = a[1][2]; b[1][1] = a[1][0]; b[1][2] = a[1][1];
	b[2][0] = a[2][0]; b[2][1] = a[2][1]; b[2][2] = a[2][2];
}

int main(int argc, char* argv[]) {
	Board board, rotatedBoard, shiftedBoard, board1;
	int yourStep, stdStep, step;
	if (argc != 4) {
		cout << "Usage:" << endl;
		cout << "num9_check inFile outFile ansFile" << endl;
		return 0;
	}
	ifstream fin(argv[1]);
	ifstream fout(argv[2]);
	ifstream fans(argv[3]);
	if (!fin) {
		cout << "Cannot open input file!" << endl;
		return 0;
	}
	if (!fout) {
		cout << "Cannot open output file!" << endl;
		return 0;
	}
	if (!fans) {
		cout << "Cannot open answer file!" << endl;
		return 0;
	}
	readBoard(fin, originBoard);
	if (!(fout >> yourStep)) {
		cout << "No -- Output format error!" << endl;
		return 0;
	}
	fans >> stdStep;
	if (yourStep != stdStep) {
		cout << "No -- The number of steps is NOT CORRECT!" << endl;
		return 0;
	}
	readBoard(fout, board);
	if (!equal(board, originBoard)) {
		cout << "No -- The first state is not the initial one!" << endl;
		return 0;
	}
	for (step = 0; step < yourStep; step++) {
		getRotatedBoard(board, rotatedBoard);
		getShiftedBoard(board, shiftedBoard);
		readBoard(fout, board1);
		if (!equal(rotatedBoard, board1) && !equal(shiftedBoard, board1)) {
			cout << "No -- Some state cannot be reached from the previous one!" << endl;
			return 0;
		}
		memcpy(board, board1, sizeof(Board));
	}
	if (!equal(board, targetBoard)) {
		cout << "No -- The last state is not the destination!" << endl;
		return 0;
	}
	cout << "Yes -- Congratulations!" << endl;
	return 0;
}
