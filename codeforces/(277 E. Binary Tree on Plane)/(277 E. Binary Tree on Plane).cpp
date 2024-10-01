#include <bits/stdc++.h>
#define y second
#define x first

using namespace std;
using DO = double;
using pid = pair<int, DO>;
using pdi = pair<DO, int>;

#define PQ priority_queue<pdi, vector<pdi>, greater<pdi> >

const DO inf = 1e9;
const int NN = 808, MM = 171717;

DO x[NN], y[NN];

struct mcmf {
	PQ q;
	int pv[NN], pe[NN], nxt[MM], to[MM];
	int V, E, head[NN], cap[MM];
    DO cost[MM], d[NN], k[NN];
	
	void add(int u, int v, int f, DO c) {
		cap[E] = f, cost[E] = c, to[E] = v, nxt[E] = head[u], head[u] = E++;
		cap[E] = 0, cost[E] = -c, to[E] = u, nxt[E] = head[v], head[v] = E++;
	}
	pid minCost(int s, int t, int x) { //max_flow <= x
		int u, e, i = V, f = 0;
        DO c = 0, g;
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
			i = V, e = x;
			while(k[i] += d[i], i--);
			for(; u ^ s; u = pv[u]) if(cap[pe[u]] < e) e = cap[pe[u]];
			x -= e, f += e, c += e * k[u = t];
			while(u ^ s) cap[pe[u]] -= e, cap[pe[u] ^ 1] += e, u = pv[u];
		}
		return {f, c};
	}
	void init(int n) {
		V = E = n + 1;
		while(head[--E] = -1, E);
	}
} mc;

DO dist(int p, int u) {
    return sqrt((x[p] - x[u]) * (x[p] - x[u]) + (y[p] - y[u]) * (y[p] - y[u]));
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lf %lf", x + i, y + i);
    
    int src = 2 * n, tar = 2 * n + 1;
    mc.init(tar);
    for(int p = n; p < 2 * n; p++) mc.add(src, p, 2, 0);
    for(int p = n; p < 2 * n; p++) {
        for(int u = 0; u < n; u++) if(y[p % n] > y[u]) {
            mc.add(p, u, 1, dist(p % n, u));
        }
    }
    for(int u = 0; u < n; u++) mc.add(u, tar, 1, 0);
    
    pid ans = mc.minCost(src, tar, n - 1);
    if(ans.x == n - 1) printf("%.15lf\n", ans.y);
    else puts("-1");
}