#include<iostream>
#include<cstring>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<functional>
#define INF 1061109567
#define MOD 998244353
#define EPS 0.000001
//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);
using namespace std;
typedef long long ll;
int x[6005], y[6005];
int first[6005], nxt[30005], edge[30005], from[30005], w[30005], cnt;
int dep[6005], cur[6005], temp[30005], used[6005], du[6005];
int n, k, s, t;
void init()
{
	memset(first, -1, sizeof(first));
	memset(nxt, -1, sizeof(nxt));
}
void add(int u, int v, int t)
{
	du[u]++;
	from[cnt] = u;
	edge[cnt] = v;
	w[cnt] = t;
	nxt[cnt] = first[u];
	first[u] = cnt++;
}
int dfs(int v, int t, int f, int cnt = INF) {
	if (v == t)return f;
	if (!cnt)return 0;
	used[v] = true;
	for (int i = first[v]; i != -1; i = nxt[i]) {
		int p = edge[i];
		if (!used[p] && w[i] > 0) {
			int d = dfs(p, t, min(f, w[i]), cnt - 1);
			if (d > 0) {
				w[i] -= d;
				w[i ^ 1] += d;
				return d;
			}
		}
	}
	return 0;
}
inline int max_flow(int s, int t) {
	int flow = 0;
	for (;;) {
		memset(used, 0, sizeof(used));
		int f = dfs(s, t, INF);
		if (f == 0)return flow;
		flow += f;
	}
}
bool check(int a, int b)
{
	return (x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]) < 4;
}
int main(void)
{
	//freopen("input.txt", "r", stdin);
	init();
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &x[i], &y[i]);
	}
	s = 0, t = n + 1;
	for (int i = 1; i <= n; i++)
	{
		if (y[i] % 2)
		{
			add(s, i, 1);
			add(i, s, 0);
		}
		else
		{
			add(i, t, 1);
			add(t, i, 0);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i != j && y[i] % 2 && !(y[j] % 2) && check(i, j))
			{
				add(i, j, INF);
				add(j, i, 0);
			}
		}
	}
	vector<int> ans;
	int flow = max_flow(s, t);
	if (n - flow < k)
	{
		printf("-1\n");
		return 0;
	}
	memcpy(temp, w, cnt * 4);
	for (int i = 1; i <= n; i++)
	{
		if (y[i] % 2)
		{
			int idx;
			for (int j = first[s]; j != -1; j = nxt[j])
			{
				if (edge[j] == i)
					idx = j, w[j] += INF;
			}
			int add_f = 0;
			if (du[i] > 1)
				add_f = max_flow(s, t);
			if (n - (flow + add_f) >= k) ans.push_back(i), flow += add_f, memcpy(temp, w, cnt * 4);
			else memcpy(w, temp, cnt * 4);
		}
		else
		{
			int idx;
			for (int j = first[i]; j != -1; j = nxt[j])
			{
				if (edge[j] == t)
					idx = j, w[j] += INF;
			}
			int add_f = 0;
			if (du[i] > 1)
				add_f = max_flow(s, t);
			if (n - (flow + add_f) >= k) ans.push_back(i), flow += add_f, memcpy(temp, w, cnt * 4);
			else memcpy(w, temp, cnt * 4);
		}
	}
	for (int i = 0; i < k; i++)
		printf("%d\n", ans[i]);
	return 0;
}
