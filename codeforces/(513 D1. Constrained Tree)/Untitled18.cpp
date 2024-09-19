#include <cstdio>
#include <cstring>
#define cs const
#define max_n 1000000
using namespace std;
typedef cs int& ci;
struct edge_node{
	int v,nxt;
	edge_node(){}
	edge_node(ci _v,ci _nxt):v(_v),nxt(_nxt){}
};
struct tree{
	int head[max_n+1],cnt;
	edge_node edge[max_n];
	void build(){
		memset(head,-1,sizeof(head)),cnt=-1;
	}
	void push(ci u,ci v){
		edge[++cnt]=edge_node(v,head[u]);
		head[u]=cnt;
	}
};
tree ltr,rtr;
int mxl[max_n+1],mnr[max_n+1],mxr[max_n+1],mxn[max_n+1];
int ans[max_n+1],*now;
void solve(ci l,ci r){
	if(l>r)
		return;
	if(mxl[l]){
		solve(l+1,mxl[l]);
		*++now=l;
		solve(mxl[l]+1,r);
	}
	else{
		*++now=l;
		solve(l+1,r);
	}
}
int main(){
	char op[6];
	int n,c;
	scanf("%d%d",&n,&c),now=ans,memset(mxl,0,sizeof(mxl)),memset(mnr,127,sizeof(mnr)),memset(mxr,0,sizeof(mxr)),ltr.build(),rtr.build();
	for(int i=c+1,a,b; --i; (op[0]=='L'?ltr:rtr).push(a,b)){
		scanf("%d%d %s",&a,&b,op);
		if(b<=a){
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	mxn[n]=n;
	for(int i=n; --i; ){
		for(int j=ltr.head[i],tmp; ~j; j=ltr.edge[j].nxt)
			(tmp=mxn[ltr.edge[j].v])>mxl[i]&&(mxl[i]=tmp);
		for(int j=i; ++j<=mxl[i]; mxn[j]>mxl[i]&&(mxl[i]=mxn[j]));
		for(int j=rtr.head[i],tmp; ~j; j=rtr.edge[j].nxt){
			(tmp=rtr.edge[j].v)<mnr[i]&&(mnr[i]=tmp);
			(tmp=mxn[tmp])>mxr[i]&&(mxr[i]=tmp);
		}
		for(int j=mnr[i]; ++j<=mxr[i]; mxn[j]>mxr[i]&&(mxr[i]=mxn[j]));
		mxn[i]=mxr[i]?mxr[i]:(mxl[i]?mxl[i]:i);
		if(mxl[i]>=mnr[i]){
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	solve(1,n);
	for(int*i=ans; ++i<=now; printf("%d ",*i));
	return 0;
}