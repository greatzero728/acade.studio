#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pi;
#define fi first
#define se second
const int N=3e5+5;
int n,m,k,sn,scc,low[N],dfn[N],st[N],c[N],bl[N],sz[N];
ll val[N],g[N],f[N];
bool ok[N];
vector<pi>e[N],E[N];
void tj(int x,int p) {
	low[x]=dfn[x]=++sn,st[++st[0]]=x;
	for(pi i:e[x]) {
		int y=i.fi;
		if(y==p)continue;
		if(!dfn[y])tj(y,x),low[x]=min(low[x],low[y]);
		else low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]) {
		int y;++scc;
		do y=st[st[0]--],val[scc]+=c[y],sz[scc]+=ok[y],bl[y]=scc;while(y!=x);
	}
}
void get(int x,int p) {
	g[x]=val[x];
	for(pi i:E[x]) {
		int y=i.fi;
		if(y!=p)get(y,x),g[x]+=sz[y]?max(0ll,g[y]-i.se):g[y],sz[x]+=sz[y];
	}
}
void dfs(int x,int p) {
	for(pi i:E[x]) {
		int y=i.fi,w=i.se;
		if(y!=p) {
			if(!sz[y])f[y]=f[x];
			else f[y]=g[y]+max(0ll,f[x]-max(0ll,g[y]-w)-w);
			dfs(y,x);
		}
	}
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,x;i<=k;i++)scanf("%d",&x),ok[x]=1;
	for(int i=1;i<=n;i++)scanf("%d",c+i);
	vector<int>w(m);for(int&i:w)scanf("%d",&i);
	for(int i=0,x,y;i<m;i++)scanf("%d%d",&x,&y),e[x].push_back({y,w[i]}),e[y].push_back({x,w[i]});
	tj(1,0);
	for(int i=1;i<=n;i++)for(pi j:e[i])if(bl[j.fi]^bl[i])E[bl[i]].push_back({bl[j.fi],j.se});
	for(int i=1;i<=scc;i++)if(sz[i]){get(i,0),f[i]=g[i],dfs(i,0);break;}
	for(int i=1;i<=n;i++)printf("%lld ",f[bl[i]]);
	return 0;
}