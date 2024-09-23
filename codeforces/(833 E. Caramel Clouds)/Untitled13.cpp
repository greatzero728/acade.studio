// LUOGU_RID: 109859000
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=3e5+10,inf=1e9;
int n,m,L[N],R[N],C[N],W,t[N],rk[N],pos[N];
struct Tree{
	#define ls (k<<1)
	#define rs (k<<1|1)
	int t[N<<2];
	void mdf(int k,int l,int r,int x,int v){
		if(l==r)return t[k]=v,void();
		int m=l+r>>1;x<=m?mdf(ls,l,m,x,v):mdf(rs,m+1,r,x,v);
		t[k]=max(t[ls],t[rs]);
	}
	int qry(int k,int l,int r,int y){
		if(!y)return 0;
		if(r<=y)return t[k];
		int m=l+r>>1;
		return max(qry(ls,l,m,y),y>m?qry(rs,m+1,r,y):0);
	}
}T;
int tmp[N*2],tp;
#define find(x) (lower_bound(tmp+1,tmp+1+tp,x)-tmp)
set<int> s;
vector<int> h[N*2]; 
int f[N],g[N],now[N*2],ans[N*2],add;
unordered_map<int,int> mp[N];
signed main(){
	n=read(),W=read();For(i,1,n)L[i]=read(),R[i]=read(),t[i]=i,C[i]=read();
	sort(t+1,t+1+n,[&](int i,int j){return C[i]<C[j];});
	For(i,1,n)rk[t[i]]=i;
	for(int i=1,j=n;i<=n;i++){
		while(j&&C[t[i]]+C[t[j]]>W)j--;
		pos[t[i]]=j;
	}
	For(i,1,n)tmp[++tp]=L[i],tmp[++tp]=R[i];tmp[++tp]=0,tmp[++tp]=2e9+10;
	sort(tmp+1,tmp+1+tp),tp=unique(tmp+1,tmp+1+tp)-tmp-1;
	For(i,1,n)h[find(L[i])].push_back(i),h[find(R[i])].push_back(-i);
	for(int i:h[1])s.insert(i),assert(i>0);
	For(x,2,tp){
		now[x]=now[x-1];int D=tmp[x]-tmp[x-1];
		if(s.size()>=3);
		else if(s.size()==2){
			int i=*s.begin(),j=*s.rbegin();
			mp[i][j]+=D;
			if(C[i]+C[j]<=W)add=max(add,mp[i][j]+f[i]+f[j]),
				g[i]=max(g[i],f[j]+mp[i][j]),g[j]=max(g[j],f[i]+mp[i][j]);
		}else if(s.size()==1){
			int i=*s.begin();
			f[i]+=D;
//			For(j,1,n)if(i!=j&&C[i]+C[j]<=W)add=max(add,f[i]+f[j]);
//			if(C[i]<=W)add=max(add,f[i]+g[i]);
			T.mdf(1,1,n,rk[i],0);
			if(C[i]<=W)add=max(add,f[i]+T.qry(1,1,n,pos[i])); 
			if(C[i]<=W)add=max(add,f[i]+g[i]);
			T.mdf(1,1,n,rk[i],f[i]);
		}else assert(s.size()==0),now[x]+=D;
		ans[x]=now[x]+add;
		for(int j:h[x])if(j>0)s.insert(j);else s.erase(-j);
//		printf("i = %d, pos = %d, add = %d, now = %d\n",x,tmp[x],add,now[x]);
	}
//	For(i,1,tp)printf("%d ",tmp[i]);puts("");
//	For(i,1,tp)printf("%d ",ans[i]);puts("");
	For(T,1,m=read()){
		int k=read();
		int i=lower_bound(ans+1,ans+1+tp,k)-ans;
		printf("%d\n",tmp[i]-(ans[i]-k)); 
	}
	return 0;
}