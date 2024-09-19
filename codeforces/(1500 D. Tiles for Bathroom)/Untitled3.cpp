// LUOGU_RID: 126090420
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int N=2005;
int n,m;
int dx[3]={-1,0,-1},dy[3]={0,-1,-1},Ans[N];
bool b[N*N];
vector<pii>v[N][N];
inline void Solve(int x,int y,int z){
	vector<pii>s;
	s.clear(),s.push_back(pii(1,z));
	for(int i=0;i<3;++i){
		for(pii j:v[x+dx[i]][y+dy[i]])s.push_back(pii(j.fi+1,j.se));
	}
	sort(s.begin(),s.end());
	for(pii i:s)if(!b[i.se]&&(int)v[x][y].size()<=m)v[x][y].push_back(i),b[i.se]=true;
	for(pii i:s)b[i.se]=false;
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1,x;j<=n;++j){
			cin>>x,Solve(i,j,x);
			int k=min(i,j);
			if((int)v[i][j].size()>m)k=min(k,v[i][j][m].fi-1);
			++Ans[k];
		}
	}
	for(int i=n;i>=1;--i)Ans[i]+=Ans[i+1];
	for(int i=1;i<=n;++i)cout<<Ans[i]<<"\n";
	return 0;
}