#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int n, l[100005], r[100005], dp[100005][2], ans;

vector<int> g[100005];

void dfs(int u, int p = 0) {
    for (int v : g[u]) if (v != p) {
        dfs(v, u);
        dp[u][0] += max(abs(l[u] - l[v]) + dp[v][0], abs(l[u] - r[v]) + dp[v][1]);
        dp[u][1] += max(abs(r[u] - l[v]) + dp[v][0], abs(r[u] - r[v]) + dp[v][1]);
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        ans = 0;
        dp[i][0] = dp[i][1] = 0;
        g[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    cout << max(dp[1][0], dp[1][1]) << endl;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t = 1; cin >> t; while (t--) solve();
    return 0;
}