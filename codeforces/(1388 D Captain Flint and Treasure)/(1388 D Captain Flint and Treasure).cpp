#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, b[N];
long long a[N], ans = 0;
vector<int> adj[N], p;

void dfs1(int u) {
    for (auto &v : adj[u]) {
        dfs1(v);
    }
    if (a[u] > 0) {
        p.push_back(u);
        ans += a[u];
        if (~b[u])a[b[u]] += a[u];
    }
}

void dfs2(int u) {
    if (a[u] <= 0) {
        ans += a[u];
        p.push_back(u);
    }
    for (auto &v : adj[u]) {
        dfs2(v);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (~b[i]) {
            adj[b[i]].push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (~b[i])continue;
        dfs1(i);
    }
    for (int i = 1; i <= n; i++) {
        if (~b[i])continue;
        dfs2(i);
    }
    cout << ans << "\n";
    for (int i = 0; i < n; i++) {
        cout << p[i] << " \n"[(i == n-1)];
    }
}