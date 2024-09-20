#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("Ofast")
#pragma GCC optimize(3)
#pragma GCC target("avx","sse2")
#include<bits/stdc++.h>
#define N 505
using namespace std;
inline int read(){int x=0,f=1;char c=getchar();while(c<48){if(c=='-')f=0;c=getchar();}while(c>=48)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
int n,m,q;
char s[N][N];
bitset<250005> f[2][505];
bool res[600005];
vector<pair<int,int> > v[250005];
inline int id(int x,int y){
	return (x-1)*m+y;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int x,y,xx,yy;scanf("%d%d%d%d",&x,&y,&xx,&yy);
		v[id(x,y)].push_back({id(xx,yy),i});
	}
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--){
			f[i&1][j].reset();
			if(s[i][j]=='.'){
				if(s[i+1][j]=='.') f[i&1][j]|=f[(i&1)^1][j];
				if(s[i][j+1]=='.') f[i&1][j]|=f[i&1][j+1];
				f[i&1][j].set(id(i,j));
			}
			for(auto u:v[id(i,j)]) res[u.second]=f[i&1][j][u.first];
		}
	for(int i=1;i<=q;i++) printf(res[i]?"Yes\n":"No\n");
	return 0;
}