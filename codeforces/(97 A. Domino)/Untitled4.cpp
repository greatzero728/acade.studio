#include<bits/stdc++.h>
using namespace std;
int calc(char C){
	if(C>='a')return C-'a';
	return 26+C-'A';
}
int n,m,sz[28],pr[14],X[28],Y[28],res,ans[28],a[33][33],cnt;
pair<int,int>pos[28][2];
char c[33][33];
bool vis[33][33];
bool Vis[49];
void check(){
	bool ok=1;
	for(register int i=0;i<14;i++){
		a[X[i]][Y[i]]=pr[i];
		a[X[i]][Y[i]+1]=pr[i];
		a[X[i]+1][Y[i]]=pr[i];
		a[X[i]+1][Y[i]+1]=pr[i];
	}
	for(register int i=0;i<49;i++)Vis[i]=0;
	for(register int i=0;i<28;i++){
		int fst=a[pos[i][0].first][pos[i][0].second];
		int snd=a[pos[i][1].first][pos[i][1].second];
		if(fst>snd)swap(fst,snd);
		if(Vis[fst*7+snd]){ok=0;return;}
		Vis[fst*7+snd]=1;
	}
	if(!res)
		for(register int i=0;i<14;i++)
			ans[i]=pr[i];
	res++;
	return;
} 
void dfs(int x){
	if(x==7){check();return;}
	for(register int i=0;i<14;i++)
		if(pr[i]==-1){
			pr[i]=x;
			for(register int j=i+1;j<14;j++)
				if(pr[j]==-1){
					pr[j]=x;
					dfs(x+1);
					pr[j]=-1;
				}
			pr[i]=-1;
			break;
		}
}
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			cin>>c[i][j];
			if(c[i][j]!='.')
				pos[calc(c[i][j])][sz[calc(c[i][j])]++]=make_pair(i,j),
				vis[i][j]=1;
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(vis[i][j]){
				vis[i][j+1]=0;
				vis[i+1][j]=0;
				vis[i+1][j+1]=0;
				X[cnt]=i;Y[cnt++]=j; 
			} 
	for(int i=0;i<14;i++)pr[i]=-1;
	dfs(0);
	cout<<res*5040<<endl;
	for(int i=0;i<14;i++){
		a[X[i]][Y[i]]=ans[i];
		a[X[i]][Y[i]+1]=ans[i];
		a[X[i]+1][Y[i]]=ans[i];
		a[X[i]+1][Y[i]+1]=ans[i];
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			if(c[i][j]=='.')
				cout<<'.';
			else
				cout<<a[i][j];
		cout<<endl;
	}
}
