#include<bits/stdc++.h>
using namespace std;
enum{N=1505};
int n,m,rs[N],vs[N*N];
vector<pair<int,int>>c[N][N],t;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1,co;i<=n;i++)for(int j=1;j<=n;j++){
        cin>>co;
        t.emplace_back(1,co);
        for(auto[d,w]:c[i-1][j])t.emplace_back(d+1,w);
        for(auto[d,w]:c[i][j-1])t.emplace_back(d+1,w);
        for(auto[d,w]:c[i-1][j-1])t.emplace_back(d+1,w);
        sort(t.begin(),t.end());
        for(auto[d,w]:t)if(!vs[w]&&c[i][j].size()<=m)c[i][j].emplace_back(d,w),vs[w]=1;
        for(auto[d,w]:t)vs[w]=0;
        t.resize(0);
        int k=min(i,j);
        if(c[i][j].size()>m)k=min(k,c[i][j][m].first-1);
        rs[k]++;
    }
    for(int i=n;i>=1;i--)rs[i]+=rs[i+1];
    for(int i=1;i<=n;i++)cout<<rs[i]<<'\n';
}