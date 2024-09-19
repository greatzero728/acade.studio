#include <bits/stdc++.h>
using namespace std;
int n,s,m,a[200010],b[200010],c[200010],t=0,x=0;
vector<pair<int,int> >E[200010];
vector<int>res[200010];
void dfs(int u){
	int v,id;
	while(E[u].size()){
		tie(v,id)=E[u].back();E[u].pop_back();
		dfs(v);
		res[x].push_back(id);
	}
}
void out(int l,int r){
	printf("%d\n",r-l+1);
	for(int i=l;i<=r;i++){
		printf("%d\n",res[i].size());
		for(int j:res[i]) printf("%d ",j);puts("");
	} 
}
int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),c[++t]=a[i];
	sort(c+1,c+t+1),t=unique(c+1,c+t+1)-c-1;
	for(int i=1;i<=n;i++) a[i]=b[i]=lower_bound(c+1,c+t+1,a[i])-c;
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++) if(a[i]^b[i]) E[a[i]].emplace_back(b[i],i);
	for(int i=1;i<=t;i++) if(E[i].size()) ++x,dfs(i),m+=res[x].size();
	if(s<m) puts("-1"),exit(0);
	int t=min(x,s-m);
	if(t<2) out(1,x);
	else{
		++x;
		for(int i=1;i<=t;i++) for(int j:res[i]) res[x].push_back(j);
		++x; 
		for(int i=t;i>=1;i--) res[x].push_back(res[i][0]);
		out(t+1,x);
	}
}