#include <bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;
using ppi = pair<pii, int>;

const int NN = 101010, MM = 202020, CC = 17;

int n, m, cnt;
int a[NN], b[NN];
ppi edge[MM];
int col[NN];
vector<int> adj[NN];

void dfs(int u) {
    col[u] = cnt;
    for(int v : adj[u]) {
        if(!col[v]) dfs(v);
    }
}

int rt[NN];

int find_root(int u) {
    return u == rt[u] ? u : rt[u] = find_root(rt[u]);
}

int head[NN], nxt[MM], to[MM], wei[MM], E;
int pa[NN][CC], mx[NN][CC], dep[NN];

void add_edge(int u, int v, int w) {
    to[E] = v, wei[E] = w, nxt[E] = head[u], head[u] = E++;
}

void lca_dfs(int u, int f = 0) {
    for(int e = head[u]; ~e; e = nxt[e]) {
        int v = to[e], w = wei[e];
        if(v != f) {
            dep[v] = dep[u] + 1;
            pa[v][0] = u, mx[v][0] = w;
            lca_dfs(v, u);
        }
    }
}

int get_lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = CC; i--; ) {
        if(dep[a] - (1 << i) >= dep[b]) a = pa[a][i];
    }
    if(a == b) return a;
    for(int i = CC; i--; ) if(pa[a][i] != pa[b][i]) {
        a = pa[a][i], b = pa[b][i];
    }
    return pa[a][0];
}

int get_max(int u, int p) {
    int ans = 0;
    for(int i = CC; i--; ) if(dep[u] - (1 << i) >= dep[p]) {
        ans = max(ans, mx[u][i]), u = pa[u][i];
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = m; i--; ) {
        scanf("%d %d %d", &edge[i].x.x, &edge[i].x.y, &edge[i].y);
        adj[edge[i].x.x].push_back(edge[i].x.y);
        adj[edge[i].x.y].push_back(edge[i].x.x);
    }
    
    for(int i = 1; i <= n; i++) if(!col[i]) {
        cnt++, dfs(i);
    }
    
    sort(edge, edge + m, [&](ppi a, ppi b) {
        return a.y < b.y;
    });
    
    for(int i = 1; i <= n; i++) {
        rt[i] = i;
        head[i] = -1;
    }
    
    INT ans = 0;
    for(int i = 0; i < m; i++) {
        int u = find_root(edge[i].x.x);
        int v = find_root(edge[i].x.y);
        int w = edge[i].y;
        if(u != v) {
            rt[u] = v, ans += w;
            add_edge(edge[i].x.x, edge[i].x.y, edge[i].y);
            add_edge(edge[i].x.y, edge[i].x.x, edge[i].y);
        }
    }
    lca_dfs(1);
    for(int j = 1; j < CC; j++) {
        for(int i = 1; i <= n; i++) {
            int f = pa[i][j - 1];
            pa[i][j] = pa[f][j - 1];
            mx[i][j] = max(mx[i][j - 1], mx[f][j - 1]);
        }
    }
    
    int q; scanf("%d", &q);
    for(int i = q; i--; ) {
        scanf("%d %d", a + i, b + i);
        if(col[a[i]] == col[b[i]]) {
            if(cnt != 1) { //case 1.2)
                puts("-1"); continue;
            }
            else { // case 1.1)
                int w = get_lca(a[i], b[i]);
                cout<<ans - max(get_max(a[i], w), get_max(b[i], w))<<endl;
            }
        }
        else {
            if(cnt != 2) { //case 2.2)
                puts("-1"); continue;
            }
            else { //case 2.1)
                cout<<ans<<endl;
            }
        }
    }
}