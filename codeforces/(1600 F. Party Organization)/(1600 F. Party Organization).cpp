#include<bits/stdc++.h>

using namespace std;
#define sz(x) (int)x.size()

void acc() {
    int n, m;
    cin >> n >> m;
    int bound = min(n, 48);
    vector<vector<bool>> vis(bound + 1, vector<bool>(bound + 1));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u <= bound and v <= bound) {
            vis[u][v] = 1;
            vis[v][u] = 1;
        }
    }
    auto check = [&](vector<int> v) {
        int sum = 0;
        for (int i = 0; i < sz(v); i++) {
            for (int j = i + 1; j < sz(v); j++) {
                sum += vis[v[i]][v[j]];
            }
        }
        return (sum == 0 or sum == 10);
    };
    for (int i = 1; i <= bound; i++) {
        for (int j = i + 1; j <= bound; j++) {
            for (int l = j + 1; l <= bound; l++) {
                for (int d = l + 1; d <= bound; d++) {
                    for (int o = d + 1; o <= bound; o++) {
                        vector<int> v;
                        v.push_back(i);
                        v.push_back(j);
                        v.push_back(l);
                        v.push_back(d);
                        v.push_back(o);
                        if (check(v)) {
                            cout << i << " " << j << " " << l << " " << d << " " << o << '\n';
                            return;
                        }
                    }
                }
            }
        }
    }
    cout << -1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    acc();
}