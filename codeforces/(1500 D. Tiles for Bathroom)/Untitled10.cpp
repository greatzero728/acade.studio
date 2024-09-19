#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define x first
#define y second
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> void chkmax(T &x,T y){x<y?x=y:T();}
template <typename T> void chkmin(T &x,T y){y<x?x=y:T();}
template <typename T> void readint(T &x)
{
	x=0;int f=1;char c;
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c-'0');
	x*=f;
}
/*const int MOD=;
inline int dmy(int x){return x>=MOD?x-MOD:x;}
inline void inc(int &x,int y){x=dmy(x+y);}
int qmi(int x,int y)
{
	int ans=1;
	for(;y;y>>=1,x=1ll*x*x%MOD)
		if(y&1)ans=1ll*ans*x%MOD;
	return ans;
}*/
const int MAXN=1505;
 
int n,q,a[MAXN][MAXN];
vector<pii> f[2][MAXN];
int vis[MAXN*MAXN],res[MAXN];
 
int main()
{
	#ifdef LOCAL
	freopen("code.in","r",stdin);
//	freopen("code.out","w",stdout);
	#endif
	readint(n),readint(q);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			readint(a[i][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			vector<pii> x=f[i&1^1][j],y=f[i&1][j-1],z;
			z.pb(mp(i,j));
			for(int u=0,v=0;u<x.size() || v<y.size();)
			{
				if(u==x.size())z.pb(y[v++]);
				else if(v==y.size())z.pb(x[u++]);
				else if(max(i-x[u].x,j-x[u].y)<max(i-y[v].x,j-y[v].y))z.pb(x[u++]);
				else z.pb(y[v++]);
			}
			f[i&1][j].clear();
			for(auto p:z)if(vis[a[p.x][p.y]]!=i*n+j)vis[a[p.x][p.y]]=i*n+j,f[i&1][j].pb(p);
			while(f[i&1][j].size()>q+1)f[i&1][j].pop_back();
			int w=(f[i&1][j].size()<=q?n:max(i-f[i&1][j][q].x,j-f[i&1][j][q].y));
			chkmin(w,min(i,j));
			++res[w];
		}
	for(int i=n;i;--i)res[i]+=res[i+1];
	for(int i=1;i<=n;++i)printf("%d\n",res[i]);
	return 0;
}
