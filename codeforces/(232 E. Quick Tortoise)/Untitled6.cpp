// LUOGU_RID: 155028449
#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef pair<int,int> pr;
const int N=505;
int n,m,q,an[600005];bitset<N>f[N][N],g[N][N];string s[N];
struct nd{int x,y,u,v,id;}f1[600005],f2[600005];
void sol(int l,int r,int gl,int gr){
	if(l>r)return;int md=l+r>>1;
	for(int i=m;i;--i)if(s[md][i]=='.')f[md][i]=f[md][i+1],f[md][i][i]=1;else f[md][i].reset();
	for(int i=md-1;i>=l;--i)for(int j=m;j;--j)if(s[i][j]=='.')f[i][j]=f[i+1][j]|f[i][j+1];else f[i][j].reset();
	for(int i=1;i<=m;++i)if(s[md][i]=='.')g[md][i]=g[md][i-1],g[md][i][i]=1;else g[md][i].reset();
	for(int i=md+1;i<=r;++i)for(int j=1;j<=m;++j)if(s[i][j]=='.')g[i][j]=g[i-1][j]|g[i][j-1];else g[i][j].reset();
	int pl=gl-1,pr=gr+1;
	for(int i=gl;i<=gr;++i)if(f1[i].x<=md&&f1[i].u>=md)an[f1[i].id]=(f[f1[i].x][f1[i].y]&g[f1[i].u][f1[i].v]).any();
	else if(f1[i].u<md)f2[++pl]=f1[i];else f2[--pr]=f1[i];
	for(int i=gl;i<=pl;++i)f1[i]=f2[i];for(int i=pr;i<=gr;++i)f1[i]=f2[i];sol(l,md-1,gl,pl);sol(md+1,r,pr,gr);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>s[i],s[i]=" "+s[i];
	cin>>q;
	for(int i=1;i<=q;++i)cin>>f1[i].x>>f1[i].y>>f1[i].u>>f1[i].v,f1[i].id=i;
	sol(1,n,1,q);
	for(int i=1;i<=q;++i)puts(an[i]?"Yes":"No");
	return 0;
}