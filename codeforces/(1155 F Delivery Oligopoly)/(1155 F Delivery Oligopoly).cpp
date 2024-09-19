#include <bits/stdc++.h>
using namespace std;
const int N = 15;
vector<pair<int, int>> ans(N * N), cur, bb(N);
vector<int> g[N], dep, b(N);
int n, m;
int dfs(int u, int fa)
{
	int low = b[u] = dep[u] = fa != N ? dep[fa] + 1 : 0;
	random_shuffle(g[u].begin(), g[u].end());
	for (auto to : g[u]) if (to != fa)
		if (dep[to] == N)
		{
			cur.emplace_back(u, to);
			low = min(low, dfs(to, u));
			if (b[u] > b[to])
				b[u] = b[to], bb[u] = bb[to];
		}
		else if (b[u] > dep[to])
			b[u] = dep[to], bb[u] = {u, to};
	if (fa != N && low == dep[u])
		low = b[u], cur.push_back(bb[u]);
	return low;
}
void hamilton() {
    cur.clear();
    for(int i = 1; i <= n; i++) dep[i] = N;
    dfs(rand() % n + 1, N);
}
int main()
{
    srand(time(0));
	scanf("%d%d", &n, &m);
	for (int i = 0, u, v; i < m; ++i)
		scanf("%d%d", &u, &v), g[u].push_back(v), g[v].push_back(u);
    for(int i = 1; i <= n; i++)
        random_shuffle(g[i].begin(), g[i].end());
    
	for (auto t = clock() + 1926; clock() < t;) {
        hamilton();
        if(cur.size() < ans.size()) ans = cur;
    }
	printf("%d\n", ans.size());
	for (auto it : ans)
		printf("%d %d\n", it.first, it.second);
}