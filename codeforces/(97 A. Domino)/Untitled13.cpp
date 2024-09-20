#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxn 32
#define intl long long
using namespace std;

intl ans;
int i,j,k,l,m,n;
int d[maxn][maxn],done[maxn][maxn],top,vis[maxn],mark[maxn][maxn],p[maxn],tp;
char s[maxn][maxn],Ans[maxn][maxn],js[maxn][maxn];

void dfs(int u) {
	int i,j;
	if (u > tp) {
		ans++;
		if (ans == 1) {
			for (i = 1; i <= n; i++) {
				for (j = 1; j <= m; j++) {
					if (s[i][j] == '.') Ans[i][j] = s[i][j];
					else Ans[i][j] = '0' + p[mark[i][j]] - 1;
				}
			}
		}
		return;
	}
	for (i = 1; i <= top; i++) {
		if (vis[i]) continue; p[u] = i;
		for (j = 1; j <= tp; j++) if ((p[j] && d[u][j] && done[i][p[j]]) || (d[u][u] && d[u][j] && u != j && p[j] == i)) break;
		if (j <= tp) { p[u] = 0; continue; }
		memset(js,0,sizeof(js));
		for (j = 1; j <= tp; j++) if (p[j] && d[u][j] && js[i][p[j]]) break; else if (p[j] && d[u][j]) js[i][p[j]] = js[p[j]][i] = 1;
		if (j > tp) {
			vis[i] = 1; p[u] = i;
			for (j = 1; j <= tp; j++) if (p[j] && d[u][j]) done[i][p[j]] = done[p[j]][i] = 1;
			dfs(u + 1);
			vis[i] = 0; 
			for (j = 1; j <= tp; j++) if (p[j] && d[u][j]) done[i][p[j]] = done[p[j]][i] = 0;		
			p[u] = 0;
		} else p[u] = 0;
	}
	if (top < 7) {
		p[u] = ++top;
		memset(js,0,sizeof(js));
		for (j = 1; j <= tp; j++) if (p[j] && d[u][j] && js[i][p[j]]) break; else if (p[j] && d[u][j]) js[i][p[j]] = js[p[j]][i] = 1;
		if (j <= tp) { p[u] = 0; top--; return; }
		for (i = 1; i <= tp; i++) if (p[i] && d[u][i]) done[top][p[i]] = done[p[i]][top] = 1;
		dfs(u + 1);
		for (i = 1; i <= tp; i++) if (p[i] && d[u][i]) done[top][p[i]] = done[p[i]][top] = 0;
		p[u] = 0; top--;
	}
}

int main() {
	scanf("%d %d",&n,&m);
	for (i = 1; i <= n; i++) scanf("%s",s[i] + 1);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++) {
			if (!mark[i][j] && s[i][j] != '.') tp++, mark[i][j] = mark[i][j + 1] = mark[i + 1][j] = mark[i + 1][j + 1] = tp;
		}
	
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++) {
			if (s[i][j] != '.' && s[i][j] == s[i + 1][j])
				d[mark[i + 1][j]][mark[i][j]] = d[mark[i][j]][mark[i + 1][j]] = 1;
			if (s[i][j] != '.' && s[i][j] == s[i][j + 1])
				d[mark[i][j + 1]][mark[i][j]] = d[mark[i][j]][mark[i][j + 1]] = 1;
		}

	dfs(1);

	cout << ans * 5040LL << endl;

	for (i = 1; i <= n; i++) printf("%s\n",Ans[i] + 1);
	return 0;
}