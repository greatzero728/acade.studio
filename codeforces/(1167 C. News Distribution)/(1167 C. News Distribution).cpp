#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005;

int par[MAXN];
int sz[MAXN];

int find(int u) {
    if (par[u] != u) {
        par[u] = find(par[u]);
    }
    return par[u];
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    sz[u] += sz[v];
    par[v] = u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        par[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        int a = -1;
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            if (a != -1) unite(a, x - 1);
            a = x - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << sz[find(i)] << " ";
    }
    cout << "\n";

    return 0;
}