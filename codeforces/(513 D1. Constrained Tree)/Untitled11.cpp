#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

 using namespace std;

#define foreach(e,x) for(__typeof((x).begin()) e=(x).begin(); e!=(x).end(); ++e)

const int N = 1000000 + 10;
const int MOD = 1e9 + 7;

int n, m;
vector<int> ls[N], rs[N];

int u, v;
int cur;
int vis[N];
char buf[10];
vector<int> ret;

void dfs(int u, int tot)
{
	vis[u] = true;
	cur ++;

	int mm = -1;
	for(int i = 0; i < ls[u].size(); ++ i) {
		mm = max(mm, ls[u][i] + 1);
	}
	if (mm != -1) {
		dfs(u + 1, mm);
	}
	ret.push_back(u);
	mm = -1;
	for(int i = 0; i < rs[u].size(); ++ i) {
		if (vis[rs[u][i]]) {
			cout << "IMPOSSIBLE" << endl;
			exit(0);
		}
		mm = max(mm, rs[u][i] + 1);
	}
	if (mm != -1 || tot > cur) {
		dfs(cur, max(tot, mm));
	}
}

void solve()
{
	cin >> n >> m;
	for(int i = 0; i < m; ++ i) {
		scanf("%d%d%s", &u, &v, buf);
		--u, --v;
		if (v <= u) {
			cout << "IMPOSSIBLE" << endl;
			return;
		}
		if (buf[0] == 'L') {
			ls[u].push_back(v);
		} else {
			rs[u].push_back(v);
		}
	}

	cur = 0;
	dfs(0, n);
	for(int i = 0; i < n; ++ i) {
		cout << ret[i] + 1 << ' ';
	}
}

int main()
{
	solve();
	return 0;
}
