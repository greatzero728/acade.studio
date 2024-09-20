#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=2000005;
int n,m,a[N],b[N],len,bb[N];
int sum[N*4],mn[N*4],tag[N*4];
vector<int> v[N],qr[N];
void pushdown(int rt){
	if(tag[rt]!=0){
		tag[rt<<1]+=tag[rt];
		tag[rt<<1|1]+=tag[rt];
		mn[rt<<1]+=tag[rt];
		mn[rt<<1|1]+=tag[rt];
		tag[rt]=0;
	}
}
void add(int rt,int l,int r,int L,int R,int x){
	if(L<=l&&r<=R){
		mn[rt]+=x,tag[rt]+=x;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(L<=mid) add(rt<<1,l,mid,L,R,x);
	if(mid<R) add(rt<<1|1,mid+1,r,L,R,x);
	mn[rt]=min(mn[rt<<1],mn[rt<<1|1]);
}
void ins(int rt,int l,int r,int x,int v){
	if(l==r) return sum[rt]+=v,void();
	int mid=(l+r)>>1;
	if(x<=mid) ins(rt<<1,l,mid,x,v);
	else ins(rt<<1|1,mid+1,r,x,v);
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
int q1(int rt,int l,int r,int L,int R){
	if(L<=l&&r<=R) return mn[rt];
	pushdown(rt);
	int mid=(l+r)>>1,s=0;
	if(L<=mid) s=min(s,q1(rt<<1,l,mid,L,R));
	if(mid<R) s=min(s,q1(rt<<1|1,mid+1,r,L,R));
	return s;
}
int q2(int rt,int l,int r,int L,int R){
	if(L<=l&&r<=R) return sum[rt];
	int mid=(l+r)>>1,s=0;
	if(L<=mid) s+=q2(rt<<1,l,mid,L,R);
	if(mid<R) s+=q2(rt<<1|1,mid+1,r,L,R);
	return s;
}
void solve(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i]),bb[i]=a[i];
	rep(i,1,m) scanf("%d",&b[i]),bb[i+n]=b[i];
	sort(bb+1,bb+n+m+1);
	len=unique(bb+1,bb+n+m+1)-bb-1;
	rep(i,1,len) v[i].clear(),qr[i].clear();
	rep(i,1,n) a[i]=lower_bound(bb+1,bb+len+1,a[i])-bb,v[a[i]].push_back(i);
	rep(i,1,m) b[i]=lower_bound(bb+1,bb+len+1,b[i])-bb,qr[b[i]].push_back(i);
	rep(i,1,4*(n+m+1)) sum[i]=0;
	long long ans=0;
	rep(i,1,n){
		ans+=q2(1,1,len,a[i]+1,len);
		ins(1,1,len,a[i],1);
	}
	rep(i,1,4*(n+m+1)) tag[i]=mn[i]=0;
	rep(i,1,n) add(1,0,n,i,n,1);
	rep(i,1,len){
		for(auto x:v[i]) add(1,0,n,x,n,-1);
		ans+=1ll*(qr[i].size())*(q1(1,0,n,0,n));
		for(auto x:v[i]) add(1,0,n,0,x-1,1);
	}
	printf("%lld\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}