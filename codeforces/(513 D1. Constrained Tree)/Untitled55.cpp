#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>
#define fi first
#define se second
#define PA pair<int,int>
#define VI vector<int>
#define VP vector<PA >
#define mk(x,y) make_pair(x,y)
#define N 1000010
#define For(i,x,y) for (i=x;i<=y;i++)
using namespace std;
struct tree {
	int mi,id,cov;
} tr[N*2*4],O;
int i,j,k,n,m,t,nn;
int L[N],R[N],zuo[N],you[N],f[N*2];
VI a[N];
inline void fail() {
	printf("IMPOSSIBLE\n");
	exit(0);
}
void print(int x) {
	if (!x) return;
	print(zuo[x]);
	printf("%d ",x);
	print(you[x]);
}
inline void update(tree &x,tree y,tree z) {
	if (y.mi<z.mi) x.mi=y.mi,x.id=y.id;
	else x.mi=z.mi,x.id=z.id;
}
inline void Inc(int x,int y) {
	tr[x].mi+=y;
	tr[x].cov+=y;
}
inline void renew(int x) {
	if (tr[x].cov) Inc(x*2,tr[x].cov),Inc(x*2+1,tr[x].cov);
	tr[x].cov=0;
}
void build(int q,int x,int y) {
	if (x==y) {
		tr[q].mi=f[x];
		tr[q].id=x;
		return;
	}
	int mid=(x+y)/2;
	build(q*2,x,mid);
	build(q*2+1,mid+1,y);
	update(tr[q],tr[q*2],tr[q*2+1]);
}
void jian(int q,int x,int y,int l,int r) {
	if (l<=x&&y<=r) {
		Inc(q,-1);
		return;
	}
	renew(q);
	int mid=(x+y)/2;
	if (l<=mid) jian(q*2,x,mid,l,r);
	if (mid<r) jian(q*2+1,mid+1,y,l,r);
	update(tr[q],tr[q*2],tr[q*2+1]);
}
void cal(int q,int x,int y,int l,int r) {
	if (l<=x&&y<=r) {
		tree w=O;
		update(O,w,tr[q]);
		return;
	}
	renew(q);
	int mid=(x+y)/2;
	if (l<=mid) cal(q*2,x,mid,l,r);
	if (mid<r) cal(q*2+1,mid+1,y,l,r);
}
inline void shan(int x) {
	int i;
	for (i=0;i<a[x].size();i++) {
		int A=a[x][i];
		jian(1,1,nn,x*2,A*2);
	}
}
void dfs(int l,int r) {
	shan(l);
	if (l==r) return;
	if (L[l]==0) {
		you[l]=l+1;
		dfs(l+1,r);
		return;
	}
	if (R[l]==N) {
		zuo[l]=l+1;
		dfs(l+1,r);
		return;
	}
	int A=L[l],B=R[l];
	if (A>=B) fail();
	{
		O.mi=N;
		cal(1,1,nn,A*2+1,B*2-1);
		if (O.mi>0) fail();
		int h=O.id/2;
		zuo[l]=l+1;
		dfs(l+1,h);
		you[l]=h+1;
		dfs(h+1,r);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	For(i,1,n) L[i]=0,R[i]=N;
	For(i,1,m) {
		int x,y; char p[10];
		scanf("%d%d%s",&x,&y,p);
		if (x>=y) fail();
		f[x*2]++; f[y*2+1]--;
		a[x].push_back(y);
		if (p[0]=='L') L[x]=max(L[x],y);
		else R[x]=min(R[x],y);
	}
	nn=n*2;
	For(i,1,nn) f[i]+=f[i-1];
	build(1,1,nn);
	dfs(1,n);
	print(1);
	printf("\n");
	return 0;
}
