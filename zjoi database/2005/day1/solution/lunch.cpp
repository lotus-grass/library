#include <fstream>
#include <algorithm>
using namespace std;

/*
#include <iostream>
#define fin cin
#define fout cout
*/

ifstream fin("lunch.in");
ofstream fout("lunch.out");

const int MAXN	=	201;
const int MAXT	=	50001;

struct Guy {
	int eat_time,get_time;
} g[MAXN+1];

bool operator< (const Guy &a,const Guy &b) {
	return a.eat_time>b.eat_time;
}

int n,ans,tot_time,s[MAXT+1];

void init() {
	int i;

	fin >> n;
	for (i=0;i<n;++i) fin >> g[i].get_time >> g[i].eat_time;
	s[0]=0;
	for (i=1;i<=MAXT;++i) s[i]=-1;
	tot_time=0;
	sort(g,g+n);
}

inline void update_choice(int & choice, const int t1,const int t2) {
	if (t1>t2) {
		if (choice<0 || t1<choice) choice=t1;
	} else {
		if (choice<0 || t2<choice) choice=t2;
	}
}

void work() {
	int i,j,choice;
	for (i=0;i<n;++i) {
		tot_time+=g[i].get_time;
		for (j=tot_time;j>=0;--j) {
			choice=-1;
			if (s[j]>=0) {
				update_choice(choice,tot_time-j+g[i].eat_time,s[j]);
			}
			if (j>=g[i].get_time && s[j-g[i].get_time]>=0) {
				update_choice(choice,j+g[i].eat_time,s[j-g[i].get_time]);
			}
			s[j]=choice;
		}
	}
	ans=-1;
	for (i=0;i<=tot_time;++i) {
		if (s[i]>=0 && (ans<0 || s[i]<ans)) ans=s[i];
	}
}

void outp() {
	fout << ans << endl;
}

int main() {
	init();
	work();
	outp();
	return 0;
}