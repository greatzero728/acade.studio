#include<bits/stdc++.h>

using namespace std;

const int NN = 3030, inf = 1e9;

vector<int> adj[NN];

int fa[NN], vst[NN], d[NN], n;

void dfs(int u) {
	vst[u] = 1;
	for(int v : adj[u]) if(v ^ fa[u]) {
		if(vst[v]) {
			for(int i = 1; i <= n; i++) d[i] = inf;
			queue<int> q;
			for(int c = u; ; c = fa[c]) {
				d[c] = 0, q.push(c);
				if(c == v) break;
			}
			
			while(!q.empty()) {
				u = q.front(); q.pop();
				for(int v : adj[u]) if(d[v] > d[u] + 1) {
					d[v] = d[u] + 1, q.push(v);
				}
			}
			for(int i = 1; i <= n; i++) printf("%d ", d[i]);
			exit(0);
		}
		fa[v] = u, dfs(v);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = n; i--; ) {
		int u, v; scanf("%d %d", &u, &v);
		adj[u].push_back(v), adj[v].push_back(u);
	}
	dfs(1);
	return 0;
}