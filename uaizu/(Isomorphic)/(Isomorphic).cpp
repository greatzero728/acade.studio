#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<int> zFunction(const T &s) {
    int n = int(s.size());
    if (n == 0) return {};
    vector<int> z(n);
    for (int i = 1, j = 0; i < n; i++) {
        int& k = z[i];
        // Calculate Z[i]
        k = (j + z[j] <= i) ? 0 : min(j + z[j] - i, z[i - j]);
        while (i + k < n && s[k] == s[i + k]) { k++; }
        if (j + z[j] < i + z[i]) { j = i; }
    }
    z[0] = n;
    return z;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    auto solve = [&]() {
        int n;
        cin >> n;
        map<vector<int>, int> mp;
        
         auto work = [&]() {
             
            vector<vector<int>> adj(n);
            vector<int> deg(n);
            for (int i = 0; i < n; i++) {
                int u, v;
                cin >> u >> v;
                u--, v--;
                adj[u].push_back(v);
                adj[v].push_back(u);
                deg[u]++;
                deg[v]++;
            }
             
            vector<int> q;
            for (int i = 0; i < n; i++) {
                if (deg[i] == 1) {
                    q.push_back(i);
                }
            }
             
             
            for (int i = 0; i < int(q.size()); i++) {
                int u = q[i];
                for (auto v : adj[u]) {
                    if (--deg[v] == 1) {
                        q.push_back(v);
                    }
                }
            }
            
             
            vector<int> roots;
            // Find roots of the components
            for (int i = 0; i < n; i++) {
                if (deg[i] > 1) {
                    int u = i, p = -1;
                    do {
                        roots.push_back(u);
                        for (auto v : adj[u]) {
                            if (deg[v] > 1 && v != p) {
                                tie(u, p) = pair(v, u);
                                break;
                            }
                        }
                    } while (u != i);
                    break;
                }
            }
             
            auto dfs = [&](auto dfs, int u, int p) -> int {
                vector<int> ch;
                for (auto v : adj[u]) {
                    if (v != p && deg[v] <= 1) {
                        ch.push_back(dfs(dfs, v, u));
                    }
                }
                sort(ch.begin(), ch.end());
                return mp.emplace(ch, mp.size()).first->second;
            };

            vector<int> res;

            for (auto s : roots) {
                res.push_back(dfs(dfs, s, -1));
            }
            return res; 
             
         };
                 
        
        
         auto a = work(), b = work();
         if (a.size() != b.size()) {
            cout << "No\n";
            return;
         }
         int len = a.size(); 
        
         for (int ite : {0, 1}) {
            vector<int> s(a);
            s.push_back(-1);
            s.insert(s.end(), b.begin(), b.end());
            s.insert(s.end(), b.begin(), b.end());
            auto z = zFunction(s);
            for (int i = len + 1; i <= 2 * len; i++) {
                if (z[i] >= len) {
                    cout << "Yes\n";
                    return;
                }
            }
            reverse(a.begin(), a.end());
        }

        cout << "No\n";        
    };
    solve();
    return 0;
}