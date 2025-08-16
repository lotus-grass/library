/*
Program		:	Top Guy
Author		:	Chen Mingcheng
*/

#include <cstdio>

const int maxn = 10000;

int list[maxn], next[maxn], data[maxn], send[maxn], receive[maxn];
int path[maxn], prev[maxn], send_all[maxn];
int n, pop, fr, to;

inline void Add_Link(int a, int b, int c, int d) {
	data[pop] = b;
	send[pop] = c;
	receive[pop] = d;
	next[pop] = list[a];
	list[a] = pop++;
}

bool DFS() {
	int curr = path[pop];
	if (curr == to) return 1;
	int i = list[curr];
	for (; i != -1; i = next[i])
		if (data[i] != prev[curr]) {
			path[++pop] = data[i];
			prev[data[i]] = curr;
			if (DFS()) return 1;
			pop--;
		}
	return 0;
}

void Init() {
	freopen("topguy.in", "r", stdin);
	freopen("topguy.out", "w", stdout);
	scanf("%d", &n);
	pop = 0;
	int i, a, b, c, d;
	for (i = 0; i < n; i++)
		list[i] = -1;
	for (i = 1; i < n; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		a--;
		b--;
		Add_Link(a, b, c, d);
		Add_Link(b, a, d, c);
	}
	scanf("%d %d", &fr, &to);
	fr--;
	to--;
	pop = 0;
	path[0] = fr;
	prev[fr] = -1;
	DFS();
	for (i = 0; i < n; i++) {
		send_all[i] = 0;
		for (a = list[i]; a != -1; a = next[a])
			send_all[i] += send[a];
	}
}

inline int Min(int a, int b) {
	return a < b ? a : b;
}

inline int Max(int a, int b) {
	return a > b ? a : b;
}

inline int Get_Max(int a, int b, int c) {
	int i, dd, ans = 0x7fffffff;
	for (i = list[b]; i != -1; i = next[i]) {
		dd = data[i];
		if (dd == a) ans = Min(ans, receive[i]);
		else
			if (dd == c) ans = Min(ans, send[i]);
			else ans = Min(ans, send_all[b] - send[i] - receive[i]);
	}
	return ans;
}

inline int Get_Min(int a, int b, int c) {
	int i, dd, left = 0, rr, ss;
	for (i = list[b]; i != -1; i = next[i]) {
		dd = data[i];
		if (dd != a && dd != c) left += send[i];
		if (dd == a) ss = receive[i];
		if (dd == c) rr = receive[i];
	}
	left -= rr - Get_Max(c, b, a);
	return Max(ss - left, 0);
}

inline int Get_Flow(int a, int b) {
	int i, dd;
	for (i = list[a]; i != -1; i = next[i]) {
		dd = data[i];
		if (dd == b) return send[i];
	}
}

void Work() {
	int ans1 = Get_Flow(path[0], path[1]), ans2 = 0x7fffffff, i;
	for (i = 1; i < pop; i++)
		ans2 = Min(ans2, Get_Max(path[i - 1], path[i], path[i + 1]));
	for (i = 1; i < pop; i++) {
		ans1 -= Get_Flow(path[i - 1], path[i]) - Get_Min(path[i - 1], path[i], path[i + 1]);
		if (ans1 <= 0) {
			ans1 = 0;
			break;
		}
	}
	printf("%d %d\n", ans1, ans2);
}

int main() {
	Init();
	Work();
	return 0;
}
