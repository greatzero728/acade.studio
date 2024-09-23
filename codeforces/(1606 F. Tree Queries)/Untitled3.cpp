#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define sz(x) ((int)x.size())
using namespace std;
const int N=200005;
int n,q,d[N],ans[N];
vector<int> G[N],dp[N];
vector<pair<int,int>> qr[N];
void dfs(int u,int fa){
	d[u]=-1;
	for(auto v:G[u]) if(v^fa){
		d[u]++,dfs(v,u);
		if(sz(dp[v])>sz(dp[u])) dp[u].resize(sz(dp[v]));
		rep(i,0,sz(dp[v])-1) dp[u][i]+=dp[v][i]; 
	}
	for(auto x:qr[u]){
		if(x.first<sz(dp[u])) ans[x.second]=dp[u][x.first];
		ans[x.second]+=d[u]+1;
	}
	if(sz(dp[u])<d[u]) dp[u].resize(d[u]);
	rep(i,0,sz(dp[u])-1) dp[u][i]+=d[u]-i;
	while(sz(dp[u])&&dp[u].back()<0) dp[u].pop_back();

}
int main(){
	scanf("%d",&n);
	rep(i,2,n){
		int x,y;
		scanf("%d%d",&x,&y);
		G[x].push_back(y),G[y].push_back(x);
	}
	scanf("%d",&q);
	rep(i,1,q){
		int x,y;
		scanf("%d%d",&x,&y);
		qr[x].emplace_back(y,i);
	}
	dfs(1,0);
	rep(i,1,q) printf("%d\n",ans[i]);
}