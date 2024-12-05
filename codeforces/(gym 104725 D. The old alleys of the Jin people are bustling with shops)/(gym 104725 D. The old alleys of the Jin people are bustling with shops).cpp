#include <bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

#define PQ priority_queue<pii, vector<pii>, greater<pii>>

const int NN = 1818, MM = 17171, inf = 1e9;

struct mcmf {
	PQ q;
	int d[NN], pv[NN], pe[NN], nxt[MM], to[MM];
	int V, E, k[NN], head[NN], cap[MM], cost[MM];
	
	void add(int u, int v, int f, int c) {
		cap[E] = f, cost[E] = c, to[E] = v, nxt[E] = head[u], head[u] = E++;
		cap[E] = 0, cost[E] = -c, to[E] = u, nxt[E] = head[v], head[v] = E++;
	}
	int minCost(int s, int t, int x) {
		int u, e, g, i = V, f = 0, c = 0;
		while(k[i] = 0, i--);
		while(x) {
			q = PQ(), i = V;
			while(d[i] = inf, i--);
			q.push({d[s] = 0, s});
			while(!q.empty()) {
				g = q.top().x, u = q.top().y, q.pop();
				if(d[u] >= g) for(e = head[u]; ~e; e = nxt[e]) if(cap[e]) {
					g = d[u] + cost[e] + k[u] - k[i = to[e]];
					if(d[i] > g) pv[i] = u, pe[i] = e, q.push({d[i] = g, i});
				}
			}
			if(d[u = t] == inf) break;
			i = V, g = x;
			while(k[i] += d[i], i--);
			for(; u ^ s; u = pv[u]) if(cap[pe[u]] < g) g = cap[pe[u]];
			x -= g, f += g, c += g * k[u = t];
			while(u ^ s) cap[pe[u]] -= g, cap[pe[u] ^ 1] += g, u = pv[u];
		}
		return c;
	}
	void init(int n) {
		V = E = n + 1;
		while(head[--E] = -1, E);
	}
} mc;

int st[33][33], ed[33][33];
int a[33][33], n, m, k;
pii ST[11], ED[11];

int calculateMaximumScore(int flowVolume) {
    int src = 0, tar = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            st[i][j] = tar++, ed[i][j] = tar++;
        }
    }
    mc.init(tar);
    
    for(int i = k; i--; ) {
        mc.add(src, st[ST[i].x][ST[i].y], 1, -100);
    }
    for(int i = k; i--; ) {
        mc.add(ed[ED[i].x][ED[i].y], tar, 1, 0);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) if(a[i][j] >= 0) {
            if(i + 1 <= n) {
                mc.add(ed[i][j], st[i + 1][j], 1, 0);
                mc.add(st[i + 1][j], ed[i][j], 1, 0);
            }
            if(j + 1 <= m) {
                mc.add(ed[i][j], st[i][j + 1], 1, 0);
                mc.add(st[i][j + 1], ed[i][j], 1, 0);
            }
            mc.add(st[i][j], ed[i][j], 1, -(a[i][j] - 1));
        }
    }
    return -mc.minCost(src, tar, flowVolume);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
    
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) scanf("%d", a[i] + j);
    }
    for(int i = k; i--; ) scanf("%d %d", &ST[i].x, &ST[i].y);
    for(int i = k; i--; ) scanf("%d %d", &ED[i].x, &ED[i].y);
    
    int maxCost = 0;
    for(int flowVolume = 1; flowVolume <= k; flowVolume++) {
        maxCost = max(maxCost, calculateMaximumScore(flowVolume));
    }
    printf("%d\n", maxCost);
    return 0;
}