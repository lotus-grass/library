#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

int n,i;

int main() {
	cin >> n;
	cout << n << endl;
	srand(time(0));
	for (i=0;i<n;++i) {
		cout << 1+rand()%200 << ' ' << 1+rand()%200 << endl;
	}
	return 0;
}