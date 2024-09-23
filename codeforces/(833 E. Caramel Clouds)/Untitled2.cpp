// LUOGU_RID: 137353584
// 2024 HOPE IN VALUABLE
#include<bits/stdc++.h>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
using namespace std;
const int N=600005;
template<typename T> inline void chkmax(T &x,T y){ x=max(x,y); }
int n,q,C,nn,h,l[N],r[N],id[N],c[N],b[N],f[N],cov[N],o[N][2],cur[N],t[N<<2];
pair<int,int>d[N]; vector<int>g[N]; set<int>s;
inline void add(int u,int l,int r,int x,int y){
	if(l==r) return t[u]+=y,void();
	int mid=l+r>>1;
	if(x<=mid) add(ls(u),l,mid,x,y);
	else add(rs(u),mid+1,r,x,y);
	t[u]=max(t[ls(u)],t[rs(u)]);
}
inline int ask(int u,int l,int r,int qr){
	if(r<=qr) return t[u];
	int mid=l+r>>1;
	if(qr<=mid) return ask(ls(u),l,mid,qr);
	return max(t[ls(u)],ask(rs(u),mid+1,r,qr));
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>C;
	for(int i=1;i<=n;i++) cin>>l[i]>>r[i]>>c[i];
	for(int i=1;i<=n;i++) b[++nn]=l[i],b[++nn]=r[i],d[i]={c[i],i}; b[++nn]=INT_MAX;
	sort(b+1,b+nn+1); sort(d+1,d+n+1); nn=unique(b+1,b+nn+1)-b-1;
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(b+1,b+nn+1,l[i])-b;
		r[i]=lower_bound(b+1,b+nn+1,r[i])-b;
		id[d[i].second]=i;
	}
	for(int i=1;i<=n;i++) g[r[i]].emplace_back(i);
	for(int i=1;i<=nn;i++) s.emplace(i);
	for(int i=1;i<=nn;i++)
		for(int j:g[i])
			for(auto it=s.upper_bound(l[j]);it!=s.end()&&*it<=r[j];){
				cov[*it]++;
				if(cov[*it]<=2) o[*it][cov[*it]-1]=j,it++;
				else it=s.erase(it);
			}
	s.clear(); for(int i=1;i<=nn;i++) s.emplace(i);
	for(int i=1;i<=nn;i++){
		f[i]=f[i-1];
		if(!cov[i]) chkmax(f[i],f[i-1]+b[i]-b[i-1]);
		else if(cov[i]==1){
			if(c[o[i][0]]<=C){
				int val=upper_bound(d+1,d+n+1,pair<int,int>{C-c[o[i][0]],n})-d-1;
				if(val) val=ask(1,1,n,val);
				chkmax(f[i],h+val+b[i]-b[i-1]);
			}
		}
		else if(cov[i]==2){
			if(c[o[i][0]]+c[o[i][1]]<=C)
				chkmax(f[i],h+b[i]-b[i-1]);
		}
		h+=b[i]-b[i-1];
		for(int j:g[i])
			for(auto it=s.upper_bound(l[j]);it!=s.end()&&*it<=r[j];){
				cur[*it]++;
				if(cur[*it]==1) add(1,1,n,id[j],b[*it]-b[*it-1]),h-=b[*it]-b[*it-1];
				else if(cur[*it]==2) add(1,1,n,id[o[*it][0]],b[*it-1]-b[*it]);
				if(cur[*it]==1) it++; else it=s.erase(it);
			}
	}
	cin>>q;
	while(q--){
		int x; cin>>x;
		int l=0,r=nn-1,pos=nn;
		while(l<=r){
			int mid=l+r>>1;
			if(f[mid]>=x) pos=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<b[pos]+x-f[pos]<<'\n';
	}
	return 0;
}