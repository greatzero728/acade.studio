#include <bits/stdc++.h>
using namespace std;
#define iinf 2000000000
#define linf 1000000000000000000LL
#define ulinf 10000000000000000000ull
#define MOD1 1000000007LL
#define mpr make_pair
typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned long UL;
typedef unsigned short US;
typedef pair < int , int > pii;
clock_t __stt;
inline void TStart(){__stt=clock();}
inline void TReport(){printf("\nTaken Time : %.3lf sec\n",(double)(clock()-__stt)/CLOCKS_PER_SEC);}
template < typename T > T MIN(T a,T b){return a<b?a:b;}
template < typename T > T MAX(T a,T b){return a>b?a:b;}
template < typename T > T ABS(T a){return a>0?a:(-a);}
template < typename T > void UMIN(T &a,T b){if(b<a) a=b;}
template < typename T > void UMAX(T &a,T b){if(b>a) a=b;}
typedef pair < int , pii > p3i;
int n,m,q,u[200005],v[200005],w[200005],rp[2],rc;
vector < int > adj[100005];
struct _DSU{
	int fa[100005];
	void init(){
		int i;
		for(i=0;i<n;++i) fa[i]=i;
	}
	int ancestor(int x){
		if(fa[x]!=x) fa[x]=ancestor(fa[x]);
		return fa[x];
	}
	void unite(int x,int y){
		x=ancestor(x);
		y=ancestor(y);
		fa[x]=y;
	}
}DSU;
struct comp{
	vector < p3i > eds;
	vector < pii > adj[100005];
	int R,fa[20][100005],fv[20][100005],rk[100005];
	LL cst;
	_DSU DSU;
	void dfs(int v,int f,int c){
		int i;
		rk[v]=(f==-1?0:(rk[f]+1));
		fa[0][v]=f;
		fv[0][v]=c;
		for(i=0;i<(int)adj[v].size();++i){
			if(adj[v][i].first!=f){
				dfs(adj[v][i].first,v,adj[v][i].second);
			}
		}
	}
	void build(){
		sort(eds.begin(),eds.end());
		DSU.init();
		int i,j,k;
		cst=0ll;
		for(i=0;i<(int)eds.size();++i){
			int u=eds[i].second.first,v=eds[i].second.second,w=eds[i].first;
			if(DSU.ancestor(u)!=DSU.ancestor(v)){
				DSU.unite(u,v);
				adj[u].push_back(mpr(v,w));
				adj[v].push_back(mpr(u,w));
				cst+=(LL)w;
				R=u;
			}
		}
		memset(fa,-1,sizeof(fa));
		dfs(R,-1,-1);
		for(i=1;i<20;++i){
			for(j=0;j<n;++j){
				if(fa[i-1][j]!=-1){
					fa[i][j]=fa[i-1][fa[i-1][j]];
					fv[i][j]=MAX(fv[i-1][j],fv[i-1][fa[i-1][j]]);
				}
			}
		}
	}
	int query(int u,int v){
		int i,R=-1;
		if(rk[u]<rk[v]) swap(u,v);
		for(i=19;i>=0;--i){
			if(fa[i][u]!=-1 && rk[fa[i][u]]>=rk[v]){
				UMAX(R,fv[i][u]);
				u=fa[i][u];
			}
		}
		if(u==v) return R;
		for(i=19;i>=0;--i){
			if(fa[i][u]!=fa[i][v]){
				UMAX(R,fv[i][u]);
				UMAX(R,fv[i][v]);
				u=fa[i][u];
				v=fa[i][v];
			}
		}
		return MAX(R,MAX(fv[0][u],fv[0][v]));
	}
}cs[2];
int main(){
    // inputting start
    // ?????????! n,m???!
    int i,j,k;
	scanf("%d%d",&n,&m);
	DSU.init();
	for(i=0;i<m;++i){
		scanf("%d%d%d",u+i,v+i,w+i);
		DSU.unite(--u[i],--v[i]);
	}
    #ifdef LOCAL
        TStart();
    #endif
    // calculation start
    // ?????????! n,m???!
    for(i=0;i<n;++i){
		int a=DSU.ancestor(i);
		for(j=0;j<rc;++j){
			if(a==rp[j]) break;
		}
		if(j==rc){
			++rc;
			if(rc==3) break;
			rp[rc-1]=a;
		}
	}
	if(rc<3) for(i=0;i<m;++i){
		for(j=0;j<rc;++j){
			if(DSU.ancestor(u[i])==rp[j]){
				cs[j].eds.push_back(mpr(w[i],mpr(u[i],v[i])));
			}
		}
	}
	if(rc<3) for(i=0;i<rc;++i){
		cs[i].build();
	}
	scanf("%d",&q);
	while(q--){
		int u,v;
		scanf("%d%d",&u,&v);
		--u;--v;
		if(rc==3)
			printf("-1\n");
		else if(rc==2){
			if(DSU.ancestor(u)!=DSU.ancestor(v)){
				printf("%I64d\n",cs[0].cst+cs[1].cst);
			}
			else printf("-1\n");
		}
		else{
			LL nc=cs[0].cst-(LL)cs[0].query(u,v);
			printf("%I64d\n",nc);
		}
	}
    #ifdef LOCAL
        TReport();
    #endif
    return 0;
}