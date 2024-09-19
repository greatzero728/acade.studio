//code bcuz love,code 4 hate
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register int
#define fr first
#define sd second
#define pa pair<int,int>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define N 2010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline int lowbit(int x){return x&(-x);}
int n,q;
int a[N][N],vis[N*N],NOW,ans[N];
vector<pa>col[N][N];
inline void calc(int x,int y)
{
	vector<pa>res;res.pb(mp(1,a[x][y]));
	for(auto tmp:col[x+1][y])res.pb(mp(tmp.fr+1,tmp.sd));
	for(auto tmp:col[x][y+1])res.pb(mp(tmp.fr+1,tmp.sd));
	for(auto tmp:col[x+1][y+1])res.pb(mp(tmp.fr+1,tmp.sd));
	sort(res.begin(),res.end());
	NOW++;
	for(auto tmp:res)
	{
		if(vis[tmp.sd]==NOW)continue;
		col[x][y].pb(tmp);vis[tmp.sd]=NOW;
		if((int)col[x][y].size()==q+1)break;
	}
}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),q=read();
	FOR(i,1,n)FOR(j,1,n)a[i][j]=read();
	REP(i,n,1)REP(j,n,1)calc(i,j);
	FOR(i,1,n)FOR(j,1,n)
	{
		int v=min(n-i+1,n-j+1);
		if((int)col[i][j].size()==q+1)v=min(v,col[i][j][q].fr-1);
		ans[v]++;
	}
	REP(i,n-1,1)ans[i]+=ans[i+1];
	FOR(i,1,n)cout<<ans[i]<<'\n';
	return 0;
}
    