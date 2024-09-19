#include <bits/stdc++.h>
#define MAXN 400010
#define INF 1000000000
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
int n,m;
vector<int> adj[MAXN];
int l[MAXN],r[MAXN],tim,a[MAXN];
ll tree[4*MAXN],lazy[4*MAXN];
void push(int node,int s,int e)
{
	if (lazy[node])
	{
		tree[node]=lazy[node];
		if (s!=e)
		{
			lazy[node*2]=lazy[node];
			lazy[node*2+1]=lazy[node];
		}
		lazy[node]=0;
	}
}
void update(int node,int s,int e,int l,int r,int val)
{
	push(node,s,e);
	if (l>e || r<s || s>e) return;
	if (l<=s && r>=e)
	{
		lazy[node]=(1LL<<val);
		push(node,s,e);
		return;
	}
	update(node*2,s,(s+e)/2,l,r,val);
	update(node*2+1,(s+e)/2+1,e,l,r,val);
	tree[node]=tree[node*2]|tree[node*2+1];
}
ll query(int node,int s,int e,int l,int r)
{
	push(node,s,e);
	if (l>e || r<s || s>e) return 0;
	if (l<=s && r>=e) return tree[node];
	return query(node*2,s,(s+e)/2,l,r)|query(node*2+1,(s+e)/2+1,e,l,r);
}
void dfs(int node)
{
	l[node]=++tim;
	for (auto i:adj[node]) if (!l[i]) dfs(i);
	r[node]=tim;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]--;
	}
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1);
	for (int i=1;i<=n;i++)
	{
		update(1,1,n,l[i],l[i],a[i]);
	}
	while (m--)
	{
		int cmd;
		scanf("%d",&cmd);
		if (cmd==1)
		{
			int v,c;
			scanf("%d%d",&v,&c);
			c--;
			update(1,1,n,l[v],r[v],c);
		}
		else
		{
			int v;
			scanf("%d",&v);
			printf("%d\n",__builtin_popcountll(query(1,1,n,l[v],r[v])));
		}
	}
	return 0;
}