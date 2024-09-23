// LUOGU_RID: 143772043
#include<bits/stdc++.h>
#define ri register int
using namespace std;
inline int rd(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
const int N=200005;
int n,m,sm[N],q;vector<int>f[N],g[N],vc[N];
void dfs(int x,int fa){
	ri o=vc[x].size()-(x!=1);
	for(auto y:vc[x])if(y!=fa){dfs(y,x);o=max(o,(int)f[y].size());}
	f[x].resize(o);
	for(auto y:vc[x])if(y!=fa){
		for(ri i=0;i<f[y].size();++i)f[x][i]+=f[y][i]-i;
		++sm[f[y].size()];
	}
	for(ri i=0;i<o;++i){f[x][i]+=sm[i];sm[i+1]+=sm[i];sm[i]=0;}sm[o]=0;
	g[x]=f[x];while(f[x].size()&&f[x].size()>=f[x].back())f[x].pop_back();
}
int main(){
	n=rd();
	for(ri i=1,x,y;i<n;++i)x=rd(),y=rd(),vc[x].push_back(y),vc[y].push_back(x);
	dfs(1,0);q=rd();
	for(ri x,y;q--;){
		x=rd();y=rd();
		if(y>=g[x].size())printf("%d\n",vc[x].size()-(x!=1));
		else printf("%d\n",g[x][y]);
	}
	return 0;
}