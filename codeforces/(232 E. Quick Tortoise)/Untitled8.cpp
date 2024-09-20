#include<bits/stdc++.h>
using namespace std;
#define y1 ___y1
const int N=505;
bitset<N> f[N][N],g[N][N];
char s[N][N];
int n,x1,y1,q,x2,y2,m,ans[600005];
struct Ask{
	int x1,y1,x2,y2,from;
	Ask(int _x1=0,int _y1=0,int _x2=0,int _y2=0,int _from=0){
		x1=_x1;y1=_y1;x2=_x2;y2=_y2;from=_from;
	}
};
vector<Ask> v;
void solve(int l,int r,vector<Ask> v){
	if (!v.size())return;
	int mid=(l+r)/2;
	vector<Ask > v1,v2,v3;
	for (Ask i:v)
		if (i.x1>mid)v2.push_back(i);
		else if (i.x2<mid)v1.push_back(i);
		else v3.push_back(i);
	solve(l,mid-1,v1);solve(mid+1,r,v2);
	for (int i=m;i;i--)
		if (s[mid][i]!='#')f[mid][i]=f[mid][i+1],f[mid][i][i]=1;
		else f[mid][i].reset();
	for (int i=mid-1;i>=l;i--)
		for (int j=m;j;j--)
			if (s[i][j]=='#')f[i][j].reset();
			else f[i][j]=f[i+1][j]|f[i][j+1];
	for (int i=1;i<=m;i++)
		if (s[mid][i]!='#')g[mid][i]=g[mid][i-1],g[mid][i][i]=1;
		else g[mid][i].reset();
	for (int i=mid+1;i<=r;i++)
		for (int j=1;j<=m;j++)
			if (s[i][j]=='#')g[i][j].reset();
			else g[i][j]=g[i-1][j]|g[i][j-1];
	for (Ask i:v3)ans[i.from]=(f[i.x1][i.y1]&g[i.x2][i.y2]).count();
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)scanf("%s",s[i]+1);
	scanf("%d",&q);
	for (int i=1;i<=q;i++){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		v.push_back(Ask(x1,y1,x2,y2,i));
	}
	solve(1,n,v);
	for (int i=1;i<=q;i++)
		if (ans[i])puts("Yes");
		else puts("No");
}
