#include<bits/stdc++.h>
#define For(i,x,y) for (int i=(x);i<=(y);i++)
#define FOR(i,x,y) for (int i=(x);i<(y);i++)
#define Dow(i,x,y) for (int i=(x);i>=(y);i--)
#define Debug(v) for (auto i:v) cout<<i<<" ";puts("")
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ep emplace_back
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define fil(a,b) memset((a),(b),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pa;
typedef pair<ll,ll> PA;
typedef vector<int> poly;
inline ll read(){
	ll x=0,f=1;char c=getchar();
	while ((c<'0'||c>'9')&&(c!='-')) c=getchar();
	if (c=='-') f=-1,c=getchar();
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}

const int N = 1e6+10;
int n,m,lsR[N],R[N],lsmx[N],rsmn[N],smx[N];

inline void GG(){
	puts("IMPOSSIBLE");exit(0);
}

int t[N];
inline void Add(int x,int y){
	for (;x<=n;x+=x&-x) t[x]=max(t[x],y);
}
inline int Query(int x){
	int ret=0;
	for (;x;x-=x&-x) ret=max(ret,t[x]);
	return ret;
}

int rt,cnt,ls[N],rs[N];
inline void solve(int &u,int L,int R){
	u=++cnt;
	if (u==R) return;
	if (u!=L) GG();
	if (lsmx[u]){
		int tmp=lsR[u];
		solve(ls[u],L+1,tmp);
		if (tmp+1<=R) solve(rs[u],tmp+1,R);
	} else {
		solve(rs[u],L+1,R);
	}
}

inline void print(int u){
	if (ls[u]) print(ls[u]);
	printf("%d ",u);
	if (rs[u]) print(rs[u]);
}

int main(){
	n=read(),m=read();
	For(i,1,n) rsmn[i]=n+1;
	For(i,1,m){
		int x=read(),y=read(),z=0;
		char op[10];
		scanf("%s",op);
		if (op[0]=='R') z=1;
		if (y<=x) GG();
		smx[x]=max(smx[x],y);
		if (z==0) lsmx[x]=max(lsmx[x],y);
			else rsmn[x]=min(rsmn[x],y);
	}
	For(i,1,n) if (lsmx[i]>=rsmn[i]) GG();
	Dow(i,n,1){
		if (lsmx[i]) lsR[i]=Query(lsmx[i]);
		if (lsR[i]>rsmn[i]) GG();
		if (smx[i]) R[i]=Query(smx[i]);
			else R[i]=i;
		Add(i,R[i]);
	}
	solve(rt,1,n),print(rt);
}