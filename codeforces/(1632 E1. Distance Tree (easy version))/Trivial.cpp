#include <bits/stdc++.h>
using namespace std;
 
 
vector<vector<int>> g;
vector<int> depth;
int max_dist;
int corr, curr;
 
 
void dfs1(int v, int p, int h) {
    depth[v] = h;
    for(int to : g[v]) {
        if(to == p) {
            continue;
        }
        dfs1(to, v, h + 1);
    }
}
 
 
void dfs2(int v, int p, int h) {
    if(h > max_dist && depth[v] > curr) {
        max_dist = h;
        corr = v;
    }
    for(int to : g[v]) {
        if(to == p) {
            continue;
        }
        dfs2(to, v, h + 1);
    }
}
 
 
int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("test.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        g.assign(n, {});
        depth.resize(n);
        for(int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs1(0, 0, 0);
 
        curr = 0;
        for(int x = 1; x <= n; ++x) {
            while(true) {
                max_dist = -1;
                corr = -1;
                for(int i = 0; i < n; ++i) {
                    if(depth[i] <= curr) {
                        continue;
                    }
                    dfs2(i, i, 0);
                    break;
                }
                if(corr == -1) {
                    break;
                }
                int v = corr;
                max_dist = -1, corr = -1;
                dfs2(v, v, 0);
                if(max_dist > 2 * (curr - x)) {
                    ++curr;
                } else {
                    break;
                }
            }
            cout << curr << ' ';
        }
        cout << '\n';
    }
}