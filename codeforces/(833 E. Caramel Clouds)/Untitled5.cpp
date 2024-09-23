// LUOGU_RID: 109581738
#include<cstdio>
#include<cctype>
#include<set>
#include<algorithm>
#include<unordered_map>

#define maxn 303303

const int inf=2e9+10;

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

template<class T>

inline void chkmax(T &a,T b){
	a=a>b?a:b;
}

struct Seg{
	int l,r,c;
	bool operator <(const Seg &seg) const{
		return c<seg.c;
	}
}seg[maxn];

struct Q{
	int k,id;
	bool operator <(const Q &q) const{
		return k<q.k;
	}
}ask[maxn];

int n,m,W,ans[maxn];

struct D{
	int num,x;
	bool operator <(const D &d) const{
		return x<d.x;
	}
}d[maxn<<1];

bool vis[maxn];

std::set<int> s;

int N,L,val[maxn],Max[maxn];

std::set<std::pair<int,int> > sta;

std::unordered_map<int,int> cross[maxn];

inline void calc(){
	for(int i=1;i<=n;i++){
		d[++N]=(D){i,seg[i].l};
		d[++N]=(D){-i,seg[i].r+1};
	}
	std::sort(d+1,d+1+N);
	d[0].x=1,d[N+1].x=inf;
	sta.insert({-1,0}),sta.insert({W+1,inf});
	int sum=0,Ans=0;
	for(int i=1,j=L;i<=N+1&&j<=m;i++){
		int len=d[i].x-d[i-1].x;
		if(!s.empty())sum+=len;
		if((int)s.size()==1){
			int num=(*s.begin());
			if(seg[num].c<=W){
				val[num]+=len;
				if(!vis[num])chkmax(Max[num],(*(--sta.lower_bound({W-seg[num].c+1,0}))).second);
				vis[num]=true,chkmax(Ans,Max[num]+=len);
			}
		}
		else if((int)s.size()==2){
			int x=(*s.begin()),y=(*s.rbegin());
			if(seg[x].c+seg[y].c<=W){
				int Val=val[x]+val[y]+(cross[x][y]+=len);
				chkmax(Max[x],Val),chkmax(Max[y],Val),chkmax(Ans,Val);
			}
		}
		int tim=d[i].x-1-sum+Ans;
		while(j<=m&&ask[j].k<=tim){
			int num=ask[j].id;
			ans[num]=ask[j++].k+sum-Ans;
		}
		if(d[i].num>0)s.insert(d[i].num);
		else {
			int id=-d[i].num;
			s.erase(id);
			if(seg[id].c>W)continue;
			auto it=sta.lower_bound({seg[id].c,0});
			while((*it).second<=val[id])sta.erase(it++);
			if((*(--it)).second<val[id])sta.insert({seg[id].c,val[id]});
		}
	}
}

int main(){
	n=read<int>();
	W=read<int>();
	for(int i=1;i<=n;i++){
		seg[i].l=read<int>()+1;
		seg[i].r=read<int>();
		seg[i].c=read<int>();
	}
	std::sort(seg+1,seg+1+n);
	m=read<int>();
    for(int i=1;i<=m;i++)
	    ask[i]=(Q){read<int>(),i};
	std::sort(ask+1,ask+1+m);
	while(L<=m&&!ask[L].k)L++;
	for(int i=L;i<=m;i++)
		ans[ask[i].id]=inf;
	calc();
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}