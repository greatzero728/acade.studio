#include <bits/stdc++.h>
using namespace std;

void fastIO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

const long long oo = 1e15;

vector<vector<pair<int,int>>> adj;
vector<int> parent;
vector<long long> dist;


struct Edge {
    int u, v;
    long long c;
};

struct MST {
    int n;
    vector<int> parent, size;
    long long minCost;

    MST(int sz) {
        n = sz;
        parent.resize(n + 1);
        size.resize(n + 1);
        minCost = 0;
    }
    
    void init() {
        for(int u = 1; u <= n; ++u){
            parent[u] = u;
            size[u] = 1;
        }
    }
    
    int find(int u) {
        if(u == parent[u])
            return u;
        return parent[u] = find(parent[u]);
    }

    bool merge(int u, int v) {
        int uP = find(u);
        int vP = find(v);

        if(vP == uP) return false;

        if(size[vP] > size[uP]) swap(uP, vP);
        size[uP] += size[vP];
        parent[vP] = uP;
        return true;
    }
    
    void build(vector<Edge> & edgs) {
        sort(edgs.begin(), edgs.end(), [&](Edge &l, Edge &r) {
            return l.c < r.c;
        });

        for(auto [u, v, c] : edgs) {
            if(merge(u, v)) {
                minCost += c;
            }
        }
    }
};

int main() {
    fastIO();
    int n, m; cin >> n >> m;
    adj.assign(n + 1, {});
    dist.assign(n + 1, oo);
    parent.assign(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    set<pair<long long, int>> s;

    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        int u; cin >> u;
        s.insert({0, u});
        dist[u] = 0;
        parent[u] = u;
    }

    while (!s.empty()){
        int u = s.begin()->second;
        s.erase(s.begin());
        for(auto [v, w] : adj[u]){
            if(dist[v] > dist[u] + w){
                s.erase({dist[v], v});
                dist[v] = dist[u] + w;
                parent[v] = parent[u];
                s.insert({dist[v], v});
            }
        }
    }
    
    vector<Edge> edges;
    for (int u = 1; u <= n; ++u) {
        for(auto [v, w] : adj[u]){
            if(parent[u] != parent[v]){
                edges.push_back({parent[u], parent[v], dist[u] + dist[v] + w});
            }
        }
    }

    MST dsu(n);
    dsu.init();
    dsu.build(edges);

    cout << dsu.minCost + dist[1] << "\n";
}
