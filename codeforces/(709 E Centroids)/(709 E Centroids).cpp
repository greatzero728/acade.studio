#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
vector<int> eg[N];
int sz[N], cen, cnt, n, ans[N];

void dfs(int u, int fa)
{
    sz[u] = 1;
    int mx = 0;
    for (int v : eg[u])
        if (v != fa)
            dfs(v, u), sz[u] += sz[v], mx = max(mx, sz[v]);
    mx = max(mx, n - sz[u]);
    if (mx <= n >> 1)
        cen = u, cnt++;
}

void slv(int u, int fa, int mod, int sum)
{
    if (sum - mod <= n >> 1)
        ans[u] = 1;
    for (int v : eg[u])
        if (v != fa)
            slv(v, u, mod, sum + sz[u] - sz[v]);
}

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int x, y;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        eg[x].push_back(y);
        eg[y].push_back(x);
    }
    dfs(1, -1);
    if (cnt == 2)
    {
        for (int i = 1; i <= n; i++)
            cout << 1 << " \n"[i == n];
        return 0;
    }
    dfs(cen, -1);
    int mx = 0, sc = 0;
    for (int v : eg[cen])
    {
        if (sz[v] > sc)
            sc = sz[v];
        if (sc > mx)
            swap(mx, sc);
    }
    ans[cen] = 1;
    for (int v : eg[cen])
        slv(v, cen, sz[v] == mx ? sc : mx, n - sz[v]);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i == n];
}