#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
using namespace std;
typedef pair<int,int> pii;
const int N=6e5+5,Inf=2e9;
int n,m,Cost;
int b[N],tag[N],l[N],r[N],add[N];
int Ctot,bC[N],C[N];
int asktot,bask[N],ask[N];
int Sum[N];
map<pii,int>SSum;
vector<int>addt[N],delt[N];
namespace BIT1{
	int c1[N],c2[N],col1[N],col2[N];
	inline void add(int x,int y,int Col){
		for(;x<=Ctot;x+=lowbit(x)){
			if(c1[x]<y){
				if(col1[x]!=Col)c2[x]=c1[x],col2[x]=col1[x];
				c1[x]=y,col1[x]=Col;
			}else if(col1[x]!=Col&&c2[x]<y)c2[x]=y,col2[x]=Col;
		}
	}
	inline int ask(int x,int Col){
		int Mx=0;
		for(;x;x-=lowbit(x)){
			if(col1[x]!=Col)Mx=max(Mx,c1[x]);
			if(col2[x]!=Col)Mx=max(Mx,c2[x]);
		}
		return Mx;
	}
}
namespace BIT2{
	int c[N];
	inline void add(int x,int y){x=asktot-x+1;for(;x<=asktot;x+=lowbit(x))c[x]=min(c[x],y);}
	inline int ask(int x){
		int Mn=Inf;x=asktot-x+1;
		for(;x;x-=lowbit(x))Mn=min(Mn,c[x]);
		return Mn;
	}
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>Cost;
	int tot=0;
	for(int i=1;i<=n;++i)cin>>l[i]>>r[i]>>C[i],b[++tot]=l[i]+1,b[++tot]=r[i]+1,bC[i]=C[i];
	b[++tot]=1,sort(b+1,b+tot+1),tot=unique(b+1,b+tot+1)-b-1;
	sort(bC+1,bC+n+1),Ctot=unique(bC+1,bC+n+1)-bC-1,bC[Ctot+1]=Inf;
	for(int i=1;i<=n;++i){
		int L=lower_bound(b+1,b+tot+1,l[i]+1)-b,R=lower_bound(b+1,b+tot+1,r[i]+1)-b;
		addt[L].push_back(i),delt[R].push_back(i),C[i]=lower_bound(bC+1,bC+Ctot+1,C[i])-bC;
	}
	cin>>m;
	for(int i=1;i<=m;++i)cin>>ask[i],bask[i]=ask[i];
	sort(bask+1,bask+m+1),asktot=unique(bask+1,bask+m+1)-bask-1,bask[asktot+1]=Inf+1;
	int Cnt0=0;
	set<int>S;
	memset(BIT2::c,127/2,sizeof(BIT2::c));
	int Mx=0;
	for(int i=1;i<tot;++i){
		for(int j:addt[i])S.insert(j);
		for(int j:delt[i])S.erase(j);
		if(!S.size()){
			Cnt0+=b[i+1]-b[i];
			int Res=Mx+b[i+1]-b[i];
			Mx=max(Mx,Res),BIT2::add(upper_bound(bask+1,bask+asktot+2,Res)-bask-1,b[i+1]-1-Res);
		}
		if(S.size()==1){
			int x=*S.begin();
			if(bC[C[x]]>Cost)continue;
			Sum[x]+=b[i+1]-b[i];
			int Res=max(Cnt0+BIT1::ask(upper_bound(bC+1,bC+Ctot+2,Cost-bC[C[x]])-bC-1,x)+Sum[x],add[x]+Sum[x]+Cnt0);
			Mx=max(Mx,Res),BIT1::add(C[x],Sum[x],x),BIT2::add(upper_bound(bask+1,bask+asktot+2,Res)-bask-1,b[i+1]-1-Res);
		}
		if(S.size()==2){
			int x=*S.begin(),y=*next(S.begin());
			if(bC[C[x]]+bC[C[y]]>Cost)continue;
			SSum[pii(x,y)]+=b[i+1]-b[i];
			int Res=Cnt0+Sum[x]+Sum[y]+SSum[pii(x,y)];
			add[x]=max(add[x],Sum[y]+SSum[pii(x,y)]),add[y]=max(add[y],Sum[x]+SSum[pii(x,y)]);
			Mx=max(Mx,Res),BIT2::add(upper_bound(bask+1,bask+asktot+2,Res)-bask-1,b[i+1]-1-Res);
		}
	}
	int Res=Mx+Inf-b[tot]+1;
	BIT2::add(upper_bound(bask+1,bask+asktot+2,Res)-bask-1,Inf-Res);
	for(int i=1;i<=m;++i)cout<<BIT2::ask(lower_bound(bask+1,bask+asktot+1,ask[i])-bask)+ask[i]<<"\n";
	return 0;
}