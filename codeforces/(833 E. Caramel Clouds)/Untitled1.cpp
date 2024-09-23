#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>pi;
#define fi first
#define se second
const int N=3e5+5,M=N*2;
int n,C,m,num,l[N],r[N],b[M],ans[N],val[N];
pi q[N];
struct node{int l,r,c;bool operator<(const node&t)const{return c<t.c;};}a[N];
vector<int>c[M];
set<int>s;
map<int,int>e[N];
struct info{
	int mx,se;
	info operator+(const info&t) {
		if(mx>t.mx)return {mx,max(se,t.mx)};
		return {t.mx,max(t.se,mx)};
	}
}t[N];
void add(int x,int k,int dt){for(;x<=n;x+=x&-x)if(t[x].mx==k)t[x].mx+=dt;else t[x]=t[x]+(info){k+dt,0};}
info ask(int x){info res={0,0};for(;x;x-=x&-x)res=res+t[x];return res;}
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>C,b[++num]=0,b[++num]=2e9+114;
	for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r>>a[i].c,b[++num]=a[i].l,b[++num]=a[i].r;
	sort(b+1,b+num+1),num=unique(b+1,b+num+1)-b-1;
	cin>>m;
	for(int i=1;i<=m;i++)cin>>q[i].fi,q[i].se=i;
	sort(q+1,q+m+1),sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) {
		a[i].l=lower_bound(b+1,b+num+1,a[i].l)-b,a[i].r=lower_bound(b+1,b+num+1,a[i].r)-b;
		c[a[i].l].push_back(i),c[a[i].r].push_back(i);
	}
	int s0=0,mx=0;
	for(int i=1,I=1;i<num;i++) {
		for(int j:c[i])if(s.find(j)==s.end())s.insert(j);else s.erase(j);
		if(!s.size())s0+=b[i+1]-b[i];
		else if(s.size()==1) {
			int x=*s.begin();
			if(a[x].c>C)continue;
			add(x,val[x],b[i+1]-b[i]),val[x]+=b[i+1]-b[i];
			int y=upper_bound(a+1,a+n+1,(node){0,0,C-a[x].c})-a-1;
			info res=ask(y);mx=max(mx,val[x]+(res.mx==val[x]&&a[x].c*2<=C?res.se:res.mx));
			for(pi j:e[x])mx=max(mx,val[x]+val[j.fi]+j.se);
		}else if(s.size()==2) {
			int x=*s.begin(),y=*s.rbegin();
			if(a[x].c+a[y].c>C)continue;
			e[x][y]+=b[i+1]-b[i],e[y][x]+=b[i+1]-b[i],mx=max(mx,val[x]+val[y]+e[x][y]);
		}
		while(I<=m&&s0+mx>=q[I].fi)ans[q[I].se]=b[i+1]-(s0+mx-q[I].fi),I++;
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<'\n';
	return 0;
}