#include<bits/stdc++.h>
using namespace std;
int n,m,q;
char s[505][505];
bool ans[600005];
bitset<505>f[505][505],g[505][505];
struct node {
	int x1,y1,x2,y2,id;
};
void solve(int l,int r,vector<node>v) {
	if(l>r)return;
	int mid=(l+r)>>1;
	for(int i=mid; i>=l; i--) {
		for(int j=m; j>=1; j--) {
			f[i][j].reset();
			if(s[i][j]=='.') {
				if(i==mid)f[i][j][j]=1;
				else f[i][j]|=f[i+1][j];
				if(j<m)f[i][j]|=f[i][j+1];
			}
		}
	}
	for(int i=mid; i<=r; i++) {
		for(int j=1; j<=m; j++) {
			g[i][j].reset();
			if(s[i][j]=='.') {
				if(i==mid)g[i][j][j]=1;
				else g[i][j]|=g[i-1][j];
				if(j>1)g[i][j]|=g[i][j-1];
			}
		}
	}
	vector<node>v1,v2;
	for(node x:v) {
		if(x.x2<mid)v1.push_back(x);
		else if(x.x1>mid)v2.push_back(x);
		else ans[x.id]=(f[x.x1][x.y1]&g[x.x2][x.y2]).any();
	}
	solve(l,mid-1,v1);
	solve(mid+1,r,v2);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) {
		scanf("%s",s[i]+1);
	}
	scanf("%d",&q);
	vector<node>v;
	v.resize(q);
	for(int i=0; i<q; i++) {
		scanf("%d%d%d%d",&v[i].x1,&v[i].y1,&v[i].x2,&v[i].y2);
		v[i].id=i;
	}
	solve(1,n,v);
	for(int i=0; i<q; i++) {
		if(ans[i])printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}