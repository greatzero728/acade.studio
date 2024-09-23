#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=4e5+50,M=550,mod=998244353;

struct node
{
	int u,v,nxt;
}e[N];

int n,x,ro[N],head[N],cnt,son[N],tot,f[M][N>>1],p[N],s,q,siz[N],ans[N],nd[N][2],g[M];

void add(int u,int v)
{
	e[++cnt]=(node){u,v,head[u]};head[u]=cnt;
	e[++cnt]=(node){v,u,head[v]};head[v]=cnt;
}

void dfs(int x,int fa)
{
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs(v,x);son[x]++;
		for(int j=0;j<=s;j++)
		f[j][x]=max(f[j][x]+1,f[j][x]+f[j][v]-j);
	}
}

void sol(int x,int fa)
{
	siz[x]=1;
	for(int i=0;i<=s;i++)f[i][x]=g[i]=-1e6;
	f[0][x]=0;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		sol(v,x);
		for(int j=0;j<=s&&j<=siz[x];j++)
		for(int k=0;k+j<=s&&k<=siz[v];k++)
		g[j+k]=max(g[j+k],f[j][x]+1),
		g[j+k+1]=max(g[j+k+1],f[j][x]+f[k][v]);
		siz[x]+=siz[v];
		for(int j=0;j<=min(s,siz[x]);j++)f[j][x]=g[j],g[j]=-1e6;
	}
}

char ch,B0[1<<15],*S=B0,*T=B0;
#define getc() (S==T&&(T=(S=B0)+fread(B0,1,1<<15,stdin),S==T)?0:*S++)
int aa;int read(){
	while(ch=getc(),ch<'0'||ch>'9');aa=ch-'0';
	while(ch=getc(),ch>='0'&&ch<='9')aa=aa*10+ch-'0';return aa;
}

main()
{
	n=read();s=sqrt(n)+100;s=min(s,n);
	for(int i=1;i<n;i++)add(read(),read());
	dfs(1,0);
	q=read();
	for(int i=1;i<=q;i++)
	{
		int v=read(),k=read();
		if(k<=s)
		{
			ans[i]=f[k][v];
			continue;
		}
		nd[i][0]=v,nd[i][1]=k;
	}
	s=n/s+1;
	sol(1,0);
	for(int i=1;i<=q;i++)
	{
		if(nd[i][0])
		{
			int ans=0;
			for(int j=0;j<=s;j++)
			ans=max(ans,f[j][nd[i][0]]-nd[i][1]*j);
			printf("%d\n",ans);
		}
		else printf("%d\n",ans[i]);
	}
}