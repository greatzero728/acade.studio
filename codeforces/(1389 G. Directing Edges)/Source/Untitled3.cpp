// LUOGU_RID: 139634873
// created:  Dec/15/2023 09:14:52
#include<cstdio>
#include<cstring>
#include<vector>
#define F(i,l,r) for(int i=(l),i##_end=(r);i<i##_end;++i)
using namespace std;
template<typename T>void readmain(T &x)
{
	bool neg=false;unsigned c=getchar();
	for(;(c^48)>9;c=getchar())if(c=='-')neg=true;
	for(x=0;(c^48)<10;c=getchar())x=(x<<3)+(x<<1)+(c^48);
	if(neg)x=-x;
}
template<typename T>T& read(T &x){readmain(x);return x;}
template<typename T,typename ...Tr>void read(T &x,Tr&... r){readmain(x);read(r...);}
constexpr int N=3e5+5;
int n,m,k,ssp[N],tag[N],ee[N][3],c[N],dep[N],ff[N],col[N],cc;
long long nc[N],f[N],g[N];
bool sp[N];
vector<int> adj[N];
vector<pair<int,int>> e[N];
int find(int x){return ff[x]==x?x:ff[x]=find(ff[x]);}
void dfs1(int u,int fa)
{
	ssp[u]=sp[u];
	for(int v:adj[u])if(v!=fa)
	{
		if(!~dep[v])dep[v]=dep[u]+1,dfs1(v,u),ssp[u]+=ssp[v],tag[u]+=tag[v];
		else if(dep[v]<dep[u])++tag[u],--tag[v];
	}
	if(ssp[u]==0||ssp[u]==k||tag[u])ff[u]=fa;
}
void dfs2(int u,int fa)
{
	f[u]=nc[u];
	for(const pair<int,int> &vw:e[u])
	{
		const int &v=vw.first,&w=vw.second;
		if(v==fa)continue;
		dfs2(v,u);
		f[u]+=max(f[v]-w,0ll);
	}
}
void dfs3(int u,int fa)
{
	f[u]+=g[u];
	for(const pair<int,int> &vw:e[u])
	{
		const int &v=vw.first,&w=vw.second;
		if(v==fa)continue;
		g[v]=max(f[u]-max(f[v]-w,0ll)-w,0ll);
		dfs3(v,u);
	}
}
int main()
{
	read(n,m,k);
	F(i,0,k)
	{
		int u;--read(u);
		sp[u]=true;
	}
	F(i,0,n)read(c[i]);
	F(i,0,m)read(ee[i][2]);
	F(i,0,m)
	{
		read(ee[i][0],ee[i][1]);--ee[i][0],--ee[i][1];
		adj[ee[i][0]].emplace_back(ee[i][1]);
		adj[ee[i][1]].emplace_back(ee[i][0]);
	}
	F(i,0,n)dep[i]=-1,ff[i]=i;
	dfs1(0,dep[0]=0);
	F(i,0,n)if(find(i)==i)col[i]=cc++;
	F(i,0,n)col[i]=col[ff[i]];
	F(i,0,n)nc[col[i]]+=c[i];
	F(i,0,m)if(col[ee[i][0]]!=col[ee[i][1]])
	{
		e[col[ee[i][0]]].emplace_back(col[ee[i][1]],ee[i][2]);
		e[col[ee[i][1]]].emplace_back(col[ee[i][0]],ee[i][2]);
	}
	dfs2(0,0);
	dfs3(0,0);
	F(i,0,n)printf("%lld ",f[col[i]]);
	puts("");
	return 0;
}
