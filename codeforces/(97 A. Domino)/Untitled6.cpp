#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

#define rep(i,l,r) for (int i=(l); i<=(r); i++)
#define repd(i,r,l) for (int i=(r); i>=(l); i--)
#define rept(i,c) for (typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)

#ifndef ONLINE_JUDGE
#define debug(x) { cerr<<#x<<" = "<<(x)<<endl; }
#else
#define debug(x) {}
#endif

int final;
int vz[7][7], vis[40][40], c[40][40], cnt[10], u[20], fu[20];
char s[40][40];
vector<int> v[30];

void dfs(int cur, int cm)
{
	if (cur==15)
	{
		memset(vz,0,sizeof vz);
		rep(i,1,28)
		{
			if (vz[u[v[i][0]]][u[v[i][1]]]) return;
			vz[u[v[i][0]]][u[v[i][1]]]=vz[u[v[i][1]]][u[v[i][0]]]=1;
		}
		final++;
		if (final==1) memcpy(fu,u,sizeof u);
		return;
	}
	rep(i,0,cm)
		if (cnt[i]<2)
		{
			cnt[i]++; u[cur]=i;
			dfs(cur+1,cm);
			cnt[i]--;
		}
	if (cm<6)
	{
		cnt[cm+1]++; u[cur]=cm+1; 
		dfs(cur+1,cm+1); 
		cnt[cm+1]--;
	}
}

void lemon()
{
	int n,m; scanf("%d%d",&n,&m); int color=0;
	rep(i,1,n)
	{
		scanf("%s",s[i]+1);
		rep(j,1,m)
		{
			if (s[i][j]!='.' && !vis[i][j])
			{
				vis[i][j]=vis[i+1][j]=vis[i][j+1]=vis[i+1][j+1]=1;
				color++; c[i][j]=c[i+1][j]=c[i][j+1]=c[i+1][j+1]=color;
			}
			if (s[i][j]!='.')
			{
				int k; if (s[i][j]>='a') k=s[i][j]-'a'+1; else k=s[i][j]-'A'+27;
				v[k].push_back(c[i][j]);
			}
		}
	}
	memset(cnt,0,sizeof cnt);
	final=0;
	dfs(1,-1);
	printf("%d\n",final*5040);
	rep(i,1,n)
		rep(j,1,m)
			if (s[i][j]!='.')
				s[i][j]='0'+fu[c[i][j]];
	
	rep(i,1,n) printf("%s\n",s[i]+1);
}

int main()
{
	ios::sync_with_stdio(true);
	#ifndef ONLINE_JUDGE
		freopen("97A.in","r",stdin);
	#endif
	lemon();
	return 0;
}