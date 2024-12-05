#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

int N, P, X, Y;
const INT INF = 1e18, inf = 1e14;

const int NN = 1010;

int flag[NN];
vector<pii> adj[NN];
INT d[NN], rd[NN];
queue<int> q;

void bfs(int X, INT tax, INT *d) {
    for(int i = 1; i <= N; i++) d[i] = INF;
    d[X] = 0, q.push(X);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(pii p : adj[u]) {
            int v = p.x; INT w = p.y + tax;
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w, q.push(v);
            }
        }
    }
}

bool impossible(INT tax) {
    for(int i = 1; i <= N; i++) d[i] = INF;
    d[X] = 0, q.push(X);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(pii p : adj[u]) {
            int v = p.x; INT w = p.y + tax;
            if(flag[v] && d[v] > d[u] + w) {
                d[v] = d[u] + w, q.push(v);
            }
        }
    }
    INT cost_using_banks = d[Y];
    
    bfs(X, tax, d);
    bfs(Y, tax, rd);
    
    INT cost_not_using_banks = INF;
    for(int i = 1; i <= N; i++) if(!flag[i]) {
        cost_not_using_banks = min(cost_not_using_banks, d[i] + rd[i]);
    }
    return cost_not_using_banks <= cost_using_banks;
}

int main() {
    while(~scanf("%d %d %d %d", &N, &P, &X, &Y)) {
        for(int i = 1; i <= N; i++) {
            flag[i] = 0;
            adj[i].clear();
        }
        while(P--) {
            int a, b, c; scanf("%d %d %d", &a, &b, &c);
            adj[a].push_back({b, c});
            adj[b].push_back({a, c});
        }
        int M; scanf("%d", &M);
        while(M--) {
            int id; scanf("%d", &id);
            flag[id] = 1;
        }
        
        if(!impossible(inf)) puts("Infinity");
        else {
            INT st = 0, ed = inf;
            while(ed - st > 1) {
                INT md = st + ed >> 1;
                if(impossible(md)) ed = md;
                else st = md;
            }
            
            if(impossible(st)) puts("Impossible");
            else printf("%lld\n", st);
        }
    }
}