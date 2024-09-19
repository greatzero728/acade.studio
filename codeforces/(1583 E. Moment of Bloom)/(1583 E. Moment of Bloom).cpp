#include<bits/stdc++.h>
using namespace std;


struct DSU{
    vector<int> parent, sizes;

    void init(int n){
        parent.resize(n+1);
        sizes.resize(n+1, 1);
        for(int i = 1; i <= n; i++) parent[i] = i;
    }

    int find_root(int u){
        if(parent[u] == u) return u;
        return parent[u] = find_root(parent[u]);
    }

    int merge(int u, int v){
        int root_u = find_root(u), root_v = find_root(v);
        if(root_u == root_v){
            return 0;
        }
        if(sizes[root_u] > sizes[root_v]){
            swap(root_u, root_v);
        }

        parent[root_u] = root_v;
        sizes[root_v] += sizes[root_u];
        return 1;
    }
};

bool dfs(int root, int parent,int target, vector<vector<int>> &graph, vector<int> &path){
    if(root == target){
        path.push_back(root);
        return true;
    }
    for(auto &ch: graph[root]){
        if(ch != parent){
            if(dfs(ch, root, target, graph, path)){
                path.push_back(root);
                return true;
            }
        }
    }

    return false;
}


signed main(){

    int n, m;
    cin >> n >> m;
    
    DSU dsu;
    dsu.init(n);

    vector<vector<int>> graph(n+1);

    int x, y;
    for(int i = 0; i < m; i++){
        cin >> x >> y;
        if(dsu.merge(x, y)){
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
    }
    
    vector<int> cnt(n+1);
    vector<pair<int,int>> queries;
    int q, a, b;
    cin >> q;
    while(q--){
        cin >> a >> b;
        queries.push_back({a,b});
        cnt[a]++;
        cnt[b]++;
    }

    int cnt_odd = 0;
    for(int i = 1; i <= n; i++){
        if(cnt[i]%2){
            cnt_odd++;
        }
    }

    if(cnt_odd){
        cout << "NO\n";
        cout << cnt_odd / 2 << endl;
    } else {
        cout << "YES\n";
        vector<int> path;
        for(auto &[u, v]: queries){
            dfs(u, -1, v, graph, path);
            cout << path.size() << endl;
            reverse(path.begin(), path.end());
            for(auto i : path) cout << i << " ";
            cout << endl;
            path.clear();
        }
    }
}