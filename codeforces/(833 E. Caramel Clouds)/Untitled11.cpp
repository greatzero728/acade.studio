#include<bits/stdc++.h>
using namespace std;
#define P pair<int,int>
const int N=900055,inf=1e9;

bool st;

int n,Q,C,Day[N];vector<int>inc[N];
int m,b[N],t,c[N],c1[N],mx[N];struct Que{int k,id;}q[N];
struct num{int l,r,c;}a[N];map<pair<int,int>,int>mp;
inline bool cmp(Que a,Que b){return a.k<b.k;}bool vst[N];
struct Dat
{
	P u,v;
	Dat friend operator +(Dat a,Dat b)
	{
		Dat c={{0,0},{0,0}};P p[4]={a.u,a.v,b.u,b.v},q[4]={{0,0},{0,0},{0,0},{0,0}};int u=0;
		sort(p,p+4);for(int i=3;i>=0;i--)if(!vst[p[i].second])vst[p[i].second]=1,q[u++]=p[i];
		c.u=q[0],c.v=q[1];for(int i=3;i>=0;i--)vst[p[i].second]=0;return c;
	}
};
struct BIT
{
	Dat c[N];inline void init(){for(int i=0;i<=t;i++)c[i]={{0,0},{0,0}};}
	inline void add(int x,Dat d){for(;x<=t;x+=(x&-x))c[x]=(c[x]+d);}
	inline Dat ask(int x){Dat w={{0,0},{0,0}};for(;x;x-=(x&-x))w=(w+c[x]);return w;}
}T;

bool ed;

inline void Init()
{
	for(int i=1;i<=n;i++)b[++m]=a[i].l,b[++m]=a[i].r,b[++m]=a[i].l-1;b[++m]=2e9;
	for(int i=1;i<=n;i++)c[++t]=a[i].c;c[++t]=C;
	sort(b+1,b+m+1),sort(c+1,c+t+1),m=unique(b+1,b+m+1)-b-1,t=unique(c+1,c+t+1)-c-1;
	for(int i=1;i<=n;i++)a[i].l=lower_bound(b+1,b+m+1,a[i].l)-b,a[i].r=lower_bound(b+1,b+m+1,a[i].r)-b;
	for(int i=1;i<=n;i++)inc[a[i].l].push_back(i),inc[a[i].r+1].push_back(-i);
}
signed main()
{
//	cout<<(&st-&ed)/1024.0/1024<<endl;
	scanf("%d%d",&n,&C);int Ans=0,clr=0,j=1;set<int>s;T.init();
	for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].c),a[i].l++;
	scanf("%d",&Q);for(int i=1;i<=Q;i++)scanf("%d",&q[i].k),q[i].id=i;sort(q+1,q+Q+1,cmp);Init();
	for(int i=1;i<=m;i++)
	{
		int len=b[i]-b[i-1],las=b[i-1];
		for(int x:inc[i]){if(x>0)s.insert(x);else s.erase(-x);}
		if(s.size()>=3)continue;
		if(s.size()==0)clr+=len;
		else if(s.size()==1)
		{
			int x=(*s.begin());
			if(a[x].c<=C)
			{
				c1[x]+=len,Ans=max(Ans,c1[x]+mx[x]);int ned=(C-a[x].c);
				if(c[t]<=ned)ned=t;else ned=upper_bound(c+1,c+t+1,ned)-c-1;
				Dat w=T.ask(ned);if(w.u.second!=x)Ans=max(Ans,c1[x]+w.u.first);
				else Ans=max(Ans,c1[x]+w.v.first);
				int p=lower_bound(c+1,c+t+1,a[x].c)-c;
				Dat v={{c1[x],x},{0,0}};T.add(p,v);
			}
		}
		else
		{
			int x=(*s.begin()),y=(*s.rbegin());
			if(a[x].c+a[y].c<=C)
			{
				mp[{x,y}]+=len;mx[x]=max(mx[x],c1[y]+mp[{x,y}]),mx[y]=max(mx[y],c1[x]+mp[{x,y}]);
				Ans=max(Ans,c1[x]+c1[y]+mp[{x,y}]);
			}
		}
		while(j<=Q&&Ans+clr>=q[j].k)Day[q[j].id]=b[i]-(Ans+clr-q[j].k),j++;
	}
	for(int i=1;i<=Q;i++)printf("%d\n",Day[i]);
	return 0;
}