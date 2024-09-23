//test
#include <bits/stdc++.h>
using namespace std;
const int N=200010;
int deg[N];
vector<int> g[N],dp[N], f[N];
void dfs(int x,int fa){
    int mx=0;
    for(auto i:g[x])if(i!=fa)dfs(i,x),++deg[x],mx=max(mx,(int)f[i].size());
    dp[x].resize(max(deg[x],mx),deg[x]);
    for(auto i:g[x])if(i!=fa)for(int k=0;k<f[i].size();k++)dp[x][k]+=f[i][k]-1;
    for(int i=0;i<dp[x].size();i++){
        if(dp[x][i]-i<=1)break;
        f[x].push_back(dp[x][i]-i);
    }
}

int main() {
    int n;cin>>n;
    for(int i=1,x,y;i<n;i++)cin>>x>>y,g[x].push_back(y),g[y].push_back(x);
    dfs(1,0);
    int q;cin>>q;
    while(q--){
        int v,k;cin>>v>>k;
        cout<<(k<dp[v].size()?dp[v][k]:deg[v])<<'\n';
    }
}