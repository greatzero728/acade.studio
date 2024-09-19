#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

int n,c;
set<int> gnext[1048576][2];
const char impossible[] = "IMPOSSIBLE";
vector<int> ans;

int nod;

void dfs(int r)
{
	int onod = nod++;
	if (onod >= n) { puts(impossible); exit(0); }
	if (gnext[onod][0].empty()) {
		ans.push_back(onod);
	} else {
		if (!gnext[onod][1].empty() && *gnext[onod][0].rbegin() >= *gnext[onod][1].begin()) { puts(impossible); exit(0); }
		if (*gnext[onod][0].begin() < nod) { puts(impossible); exit(0);}
		dfs (*gnext[onod][0].rbegin());
		ans.push_back(onod);
	}
	if (!gnext[onod][1].empty()) {
		if (*gnext[onod][1].begin() < nod) { puts(impossible); exit(0);}
		dfs (max(r,*gnext[onod][1].rbegin()));
	} else if (nod <= r) dfs (r);
}

int main(){
	scanf("%d%d",&n,&c);
	for (int i = 0; i < c; i++) {
		char str[20];
		int a,b;
		scanf("%d%d%s", &a, &b, str);
		a--,b--;
		if (a >= b) {
			puts(impossible);
			return 0;
		}
		if (str[0] == 'L') gnext[a][0].insert(b);
		else gnext[a][1].insert(b);
	}
	dfs(n-1);
	for (int i = 0; i < n; i++) {
		printf("%d%c", ans[i] + 1, " \n"[i+1 == n]);
	}
	return 0;
}