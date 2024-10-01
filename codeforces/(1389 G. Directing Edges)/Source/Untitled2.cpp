// LUOGU_RID: 123783218
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+5;
int n,m,k;
int w[N],c[N],X[N],Y[N];
bool tag[N];
vector<int>e[N];
int dfn[N],low[N],sign,st[N],tot,bt[N],num;
void tarjan(int x,int prt){
	dfn[x]=low[x]=++sign,st[++tot]=x;
	for(int y:e[x]){
		if(!dfn[y])tarjan(y,x),low[x]=min(low[x],low[y]);
		else if(y!=prt)low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int y;++num;
		do{y=st[tot--],bt[y]=num;}while(y!=x);
	}
}
struct Cx{int to,val;};
vector<Cx>E[N];
int Siz[N],W[N];
ll f[N],V[N],Ans[N];
void dfs1(int x,int prt){
	Siz[x]=W[x],f[x]=V[x];
	for(Cx u:E[x]){
		int y=u.to;
		if(y==prt)continue;
		dfs1(y,x),Siz[x]+=Siz[y];
		f[x]+=max(f[y]-u.val*(Siz[y]!=k&&Siz[y]!=0),0ll);
	}
}
void dfs2(int x,int prt){
	ll Res=f[x],S=Siz[x];
	Siz[x]=k,f[x]=V[x];
	for(Cx u:E[x])f[x]+=max(f[u.to]-u.val*(Siz[u.to]!=k&&Siz[u.to]!=0),0ll);
	Ans[x]=f[x];
	for(Cx u:E[x]){
		int y=u.to;
		if(y==prt)continue;
		Siz[x]-=Siz[y],f[x]-=max(f[y]-u.val*(Siz[y]!=k&&Siz[y]!=0),0ll);
		dfs2(y,x);
		Siz[x]+=Siz[y],f[x]+=max(f[y]-u.val*(Siz[y]!=k&&Siz[y]!=0),0ll);
	}
	Siz[x]=S,f[x]=Res;
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1,x;i<=k;++i)cin>>x,tag[x]=true;
	for(int i=1;i<=n;++i)cin>>c[i];
	for(int i=1;i<=m;++i)cin>>w[i];
	for(int i=1,x,y;i<=m;++i)cin>>x>>y,e[x].push_back(y),e[y].push_back(x),X[i]=x,Y[i]=y;
	tarjan(1,0);
	for(int i=1;i<=n;++i)V[bt[i]]+=c[i],W[bt[i]]+=tag[i];
	for(int i=1;i<=m;++i)if(bt[X[i]]!=bt[Y[i]])E[bt[X[i]]].push_back((Cx){bt[Y[i]],w[i]}),E[bt[Y[i]]].push_back((Cx){bt[X[i]],w[i]});
	dfs1(1,0),dfs2(1,0);
	for(int i=1;i<=n;++i)cout<<Ans[bt[i]]<<" ";
	return 0;
}