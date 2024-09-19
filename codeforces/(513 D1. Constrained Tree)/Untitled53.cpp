#include<bits/stdc++.h>
using namespace std;
const int N=105;
vector<int> G[N],L[N],R[N];
set<int> son[N][2],tmp,rec[N][N];
int sta[N][N],ans[N],c[N],cnt[N],n,m,x,y,LA,cur;
char st[10];
void Term(){ puts("IMPOSSIBLE"); exit(0); }
void dfs(int u, int rt, int k){
	if (sta[rt][u]==(k^1)) Term();
	if (sta[rt][u]==k) return;
	sta[rt][u]=k; son[rt][k].insert(u);
	for (int v:G[u])
		if (c[v]) dfs(v,rt,k);
}
void Get(int u, int rt){
	if (sta[rt][u]!=-1) return;
	sta[rt][u]=1; rec[rt][cnt[rt]].insert(u);
	for (int v:G[u])
		if (c[v]) Get(v,rt);
}
void dfs(set<int> S){
	if (S.empty()) return;
	int rt=*S.begin(); S.erase(rt);
	for (int i:S) c[i]=1;
	for (int i:L[rt]) if (c[i]) dfs(i,rt,0);
	for (int i:R[rt]) if (c[i]) dfs(i,rt,1);
	for (int i:S) if (sta[rt][i]==-1) cnt[rt]++,Get(i,rt);
	for (int i:S) c[i]=0;
	int mx=son[rt][0].empty()?-1:(*son[rt][0].rbegin());
	int mn=son[rt][1].empty()?n+1:(*son[rt][1].begin());
	if (mx>mn) Term();
	
	for (int i=mx; i<=mn; i++){
		bool flag=0;
		for (int j=1; j<=cnt[rt]; j++)
			if ((*rec[rt][j].begin())<=i && i<(*rec[rt][j].rbegin())){ flag=1; break; }
		if (!flag){
			for (int j=1; j<=cnt[rt]; j++)
				if ((*rec[rt][j].rbegin())<=i){
					for (int x:rec[rt][j]) son[rt][0].insert(x);
				} else {
					for (int x:rec[rt][j]) son[rt][1].insert(x);
				}
			dfs(son[rt][0]);
			ans[++LA]=rt;
			dfs(son[rt][1]);
			return;
		}
	}
//	printf("==>%d\n",rt);
	Term();
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++){
		scanf("%d%d%s",&x,&y,st+1);
		if (x>=y) Term();
		if (st[1]=='L') L[x].push_back(y);
		else R[x].push_back(y);
		G[x].push_back(y),G[y].push_back(x);
	}
	memset(sta,-1,sizeof(sta));
	for (int i=1; i<=n; i++) tmp.insert(i);
	
	dfs(tmp);
	for (int i=1; i<=n; i++) printf("%d ",ans[i]); puts("");
}
/*
25 10
3 5 R
8 10 L
8 12 L
8 17 L
1 19 R
6 21 R
1 22 R
6 24 R
6 25 R
23 24 R

3 3
1 2 L
2 3 L
1 3 R

3 2
1 2 LEFT
1 3 RIGHT

20 40
1 9 R
1 9 R
1 17 R
1 17 R
1 12 R
1 12 R
1 7 L
1 7 L
1 4 L
1 4 L
2 3 L
2 3 L
2 7 R
2 7 R
2 8 R
2 8 R
5 6 L
5 6 L
5 7 L
5 7 L
5 8 R
5 8 R
9 13 L
9 13 L
9 16 L
9 16 L
9 14 L
9 14 L
9 19 R
9 19 R
9 17 R
9 17 R
11 12 L
11 12 L
11 13 L
11 13 L
17 19 L
17 19 L
17 20 R
17 20 R

7 7
1 3 L
1 6 L
1 7 R
2 3 L
2 5 R
4 5 L
4 6 R
*/
