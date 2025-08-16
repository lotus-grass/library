#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 30;
const int MAXM = 30;
const int MAXP = 100000;
const int MAXV = 2 * MAXN * MAXN + MAXN + MAXM + 2;

const int ITER = 40;
const int FLOW_ITER = 40;
const double EPS = 1e-9;
const double DEPS = 1e-8; // Double contains at most 15 decimal digits

struct tEdge {
	double c, f;
	int to, r;
	tEdge(int _to = -1, double _c = 0.0, int _r = -1) : c(_c), f(0.0), to(_to), r(_r) {}
};

int n, m, p[MAXN], r[MAXN], d[MAXN], s[MAXM];
vector<tEdge> c[MAXV];
int vs, vt, nv;
bool u[MAXV];

inline int dcmp(double d1, double d2) {
	return fabs(d1 - d2) <= DEPS;
}

inline int addV() { 
	c[nv].clear(); 
	return nv++; 
}

inline void addE(int a, int b, double ca) {
	c[a].push_back(tEdge(b, ca, c[b].size()));
	c[b].push_back(tEdge(a, 0, c[a].size() - 1));
}

bool DFS(int v, double delta) {
	if (v == vt) return true;
	u[v] = true;
	for (int i = 0; i < (int)c[v].size(); ++i) {
		tEdge &t = c[v][i];
 		if (t.f + delta <= t.c && !u[t.to] && DFS(t.to, delta)) {
			t.f += delta; 
			c[t.to][t.r].f -= delta;
			return true;
		}
	}
  	return false;
}

double maxFlow() {
	double cu = 1 << 20, sum = 0;
	for (int i = 0; i < FLOW_ITER; ++i, cu *= 0.5) {
		while (1) {
			memset(u, 0, sizeof(u));
			if (!DFS(vs, cu)) break;
			sum += cu;
		}
	}
  	return sum;
}

bool check(double add) {
	nv = 0;
	vs = addV();
	vt = addV();
	int vj = nv;
	for (int i = 0; i < n; ++i)
		addE(addV(), vt, (double)p[i]);
	
	vector<double> ti;
	for (int i = 0; i < n; ++i) {
		ti.push_back((double)r[i]);
		ti.push_back(d[i] + add);
	}
  
	/* remove duplicate values */
	sort(ti.begin(), ti.end());
	ti.erase(unique(ti.begin(), ti.end(), dcmp), ti.end());
  
	for (int i = 1; i < (int)ti.size(); ++i) {
		double dt = ti[i] - ti[i - 1];
		int vc = nv;
		for (int j = 0; j < m; ++j)
			addE(vs, addV(), dt * s[j] * (j + 1));
		for (int j = 0; j < m; ++j)
			for (int k = 0; k < n; ++k)
				if (r[k] - EPS <= ti[i - 1] && ti[i] <= d[k] + add + EPS)
					addE(vc + j, vj + k, dt * s[j]);
	}
	
	int need = 0;
	for (int i = 0; i < n; ++i) need += p[i];
	
	return fabs(maxFlow() - need) < EPS;
}

int main() {
	freopen("cheese.in", "r", stdin);
	freopen("cheese.out", "w", stdout);

	int testcases;
	int __maxn = 0, __maxm = 0;

	scanf("%d", &testcases);
	while (testcases--) {
		scanf("%d %d", &n, &m);
		__maxn >?= n;
		__maxm >?= m;
		for (int i = 0; i < n; ++i)
    		scanf("%d %d %d", &p[i], &r[i], &d[i]);
  	
	  	for (int i = 0; i < m; ++i) 
    		scanf("%d", &s[i]);
    	
		sort(s, s + m, greater<int>());
  		for (int i = 0; i < m - 1; ++i)	
		    s[i] -= s[i + 1];
	    
		double mi = 0.0, ma = MAXN * MAXP;
  		for (int i = 0; i < ITER; ++i) {
			double av = (mi + ma) * 0.5;
			if (check(av))
				ma = av;
			else
				mi = av;
		}
		printf("%.7lf\n", mi);
	}

	printf("%d %d\n", __maxn, __maxm);

	return 0;
}

