#include <iostream>
#include <algorithm>

using namespace std;

int contain(int s, int i)
{
	return (s & (1 << i)) ? 1 : 0;
}

int	main()
{
	freopen("knight.in", "r", stdin);
	freopen("knight.out", "w", stdout);

	int N;
	cin >> N;
	if (N > 20) exit(0);
	
	int value[30], hate[30];
	for (int i = 0; i < N; ++i) cin >> value[i] >> hate[i], --hate[i];

	int answer = 0;
	for (int s = 0; s < (1 << N); ++s)
	{
		bool fit = 1;
		int cnt = 0;
		for (int i = 0; i < N; ++i) 
		{
			if (contain(s, i) && contain(s, hate[i])) fit = 0;
			cnt += contain(s, i) * value[i];
		}
		if (fit) answer = max(answer, cnt);
	}
	cout << answer << endl;
	return 0;
}
