#include "bits/stdc++.h"

using namespace std;

vector<int> p;

int find(int u) {
    if (u == p[u]) return u;
    return p[u] = find(p[u]);
}

bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    p[u] = v;
    return true;
}

signed main() {
    int n;
    cin >> n;
    vector<int> x(n + 1), y(n + 1), c(n + 1), k(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> x[i] >> y[i];

    for (int i = 1; i <= n; ++i)
        cin >> c[i];

    for (int i = 1; i <= n; ++i)
        cin >> k[i];

    vector<array<long long, 3>> edges;
    for (int i = 1; i <= n; ++i)
        edges.push_back({c[i], 0, i});

    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            long long cost = 1LL * (k[i] + k[j]) * (abs(x[i] - x[j]) + abs(y[i] - y[j]));
            edges.push_back({cost, i, j});
        }

    p.resize(n + 1);
    for (int i = 1; i <= n; ++i)
        p[i] = i;

    sort(edges.begin(), edges.end());

    vector<int> power;
    vector<pair<int, int>> connection;
    long long tot = 0;

    for (auto &[cost, i, j]: edges) {
        if (merge(i, j)) {
            if (i) connection.push_back({i, j});
            else power.push_back(j);
            tot += cost;
        }
    }

    cout << tot << '\n';
    cout << power.size() << '\n';
    for (int &i: power) cout << i << ' ';
    cout << '\n' << connection.size() << '\n';
    for (auto &[u, v]: connection)
        cout << u << ' ' << v << '\n';
}