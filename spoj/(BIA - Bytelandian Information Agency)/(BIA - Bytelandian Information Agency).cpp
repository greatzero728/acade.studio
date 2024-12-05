#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 1;
vector<int>adj[N];
bitset<N>vis , ArtPoint;
void dfs(int u) {
    vis[u] = true;
    for(auto &val:adj[u]) {
        if(!vis[val])dfs(val);
    }
}
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n , m;
    while(cin>>n>>m) {
        for(int i = 1;i <= n;i++)adj[i].clear();
        ArtPoint.reset();
        for(int i = 0;i < m;i++) {
            int a , b;cin>>a>>b;
            adj[a].emplace_back(b);
        }
        for(int i = 2;i <= n;i++) {
            vis.reset(); vis[i] = true;
            dfs(1);
            if(vis.count() != n)ArtPoint[i] = true;
        }
        ArtPoint[1] = true;
        cout<<ArtPoint.count()<<'\n';
        for(int i = 1;i <= n;i++) {
            if(ArtPoint[i])cout<<i<<" ";
        }
        cout<<'\n';
    }
}
