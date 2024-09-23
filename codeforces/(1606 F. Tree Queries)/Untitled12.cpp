#include<bits/stdc++.h>
using namespace std;
int n,m,qv[200003],qk[200003],dp[453][200003],qans[200003];
vector<int>v[200003];
void dfs(int x,int p){
	for(int i=0;i<v[x].size();i++)
		if(v[x][i]!=p){
			dfs(v[x][i],x);
			for(register int j=0;j<453;j++)
				dp[j][x]+=max(1,dp[j][v[x][i]]-j);
		}
}
void DFS(int x,int p){
	for(register int i=0;i<453;i++)
		dp[i][x]=0;
	for(int i=0;i<v[x].size();i++)
		if(v[x][i]!=p){
			DFS(v[x][i],x);
			int qaq=0;
			for(register int j=0;j<453;j++)
				qaq=max(qaq,dp[j][v[x][i]]-j*450);
			if(qaq>=450)
				for(register int j=452;j>=0;j--)
					for(register int k=0;k<j;k++)
						dp[j][x]=max(dp[j][x],dp[j-k-1][x]+dp[k][v[x][i]]-1);
			for(register int j=0;j<453;j++)
				dp[j][x]++;
		}
}
int main(){
//	freopen("a.in","r",stdin);
	cin>>n;
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		a--;b--;
		v[a].push_back(b);
		v[b].push_back(a);
	}cin>>m;
	for(int i=0;i<m;i++)
		scanf("%d%d",qv+i,qk+i),
		qv[i]--;
	dfs(0,-1);
	for(int i=0;i<m;i++)
		if(qk[i]<453)
			qans[i]=dp[qk[i]][qv[i]];
	DFS(0,-1);
	for(int i=0;i<m;i++)
		if(qk[i]>=453)
			for(int j=0;j<453;j++)
				qans[i]=max(qans[i],dp[j][qv[i]]-j*qk[i]);
	for(int i=0;i<m;i++)
		printf("%d\n",qans[i]);
}
