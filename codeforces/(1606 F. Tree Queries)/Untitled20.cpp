#include<bits/stdc++.h>
//#define int long long
using namespace std;
typedef long long LL;
const int N=200010,M=455;
int f[N][M];
int n,q,sz[N],temp[M];
int h[N],ne[N<<1],e[N<<1],idx;
int ans[N];
void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void dfs1(int u,int fa)
{
    for (int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if (j==fa) continue;
        dfs1(j,u);
        for (int k=0;k<M;k++) f[u][k]+=max(1,f[j][k]-k);
    }
}
void dfs2(int u,int fa)
{
    sz[u]=1;
    for (int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if (j==fa) continue;
        dfs2(j,u);
        for (int k=0;k<=sz[u]+sz[j]&&k<M;k++) temp[k]=0;
        for (int k=0;k<=sz[u]&&k<M;k++)
            for (int x=0;x<=sz[j]&&x+k<M;x++)
            {
                temp[x+k]=max(temp[x+k],f[u][k]+1);
                if (x+k+1<M) temp[x+k+1]=max(temp[x+k+1],f[u][k]+f[j][x]);
            }
        sz[u]+=sz[j];
        for (int k=0;k<=sz[u]&&k<M;k++) f[u][k]=temp[k];
    }
}
void solve()
{
    memset(h,-1,sizeof h);
    cin>>n;
    for (int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    cin>>q;
    vector<array<int,3>> Q1,Q2;
    for (int i=1;i<=q;i++)
    {
        int v,k;
        cin>>v>>k;  
        if (k<M) Q1.push_back({v,k,i});
        else Q2.push_back({v,k,i});
    }
    dfs1(1,0);
    for (auto [v,k,id]:Q1) ans[id]=f[v][k];
    memset(f,0,sizeof f);
    dfs2(1,0);
    for (auto [v,k,id]:Q2)
        for (int i=(n+k-1)/k;i>=0;i--)
            ans[id]=max(ans[id],f[v][i]-k*i);
    for (int i=1;i<=q;i++) cout<<ans[i]<<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);
    solve();
    return 0;
}