#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;
const int MAX = 105;
vector<int> adj[2][MAX];
vector<int> neg[MAX];
bool mark[MAX], mark2[MAX], can = true;
int ans[MAX], n, m;
int cnt = 0;
void dfs(int v)
{
	mark[v] = true;
	cnt++;
	for (int i = 0; i < neg[v].size(); i++)
	{
		int u = neg[v][i];
		if (!mark[u] && !mark2[u])
			dfs(u);
	}
}
void solve(int s, int e, int l, int r)
{
	if (s >= e)
		return;
	mark2[s] = true;
	memset(mark, false, sizeof(mark));
	int mx = s;
	for (int i = 0; i < adj[0][s].size(); i++)
	{
		int v = adj[0][s][i];
		dfs(v);
	}
	while (true)
	{
		for (int i = 0; i < n; i++)
			if (mark[i])
				mx = i;
		cnt = 0;
		for (int i = s + 1; i <= mx; i++)
			if (!mark[i])
				dfs(i);
		if (cnt == 0)
			break;
	}
	for (int i = 0; i < adj[0][s].size(); i++)
	{
		int v = adj[0][s][i];
		if (v < s + 1 || mx + 1 <= v)
		{
		cout << "IMPOSSIBLE" << endl;
		exit(0);
		}
	}
	for (int i = 0; i < adj[1][s].size(); i++)
	{
		int v = adj[1][s][i];
		if (v < mx + 1 || e <= v)
		{
		cout << "IMPOSSIBLE" << endl;
		exit(0);
		}
	}
	if (mx >= e)
		{
		cout << "IMPOSSIBLE" << endl;
		exit(0);
		}
	ans[l + mx - s] = s;
	solve(s + 1, mx + 1, l, l + mx - s);
	solve(mx + 1, e, l + mx - s + 1, r);
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	while (m--)
	{
		int x, y;
		string s;
		cin >> x >> y >> s;
		x--;
		y--;
		if (s == "LEFT")
			adj[0][x].push_back(y);
		else	
			adj[1][x].push_back(y);
		neg[x].push_back(y);
		neg[y].push_back(x);
	}
	solve(0, n, 0, n);
	if (can == false)
	{
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	for (int i = 0; i < n; i++)
		cout << ans[i] + 1 << " ";
	cout << endl;
	return 0;
}
