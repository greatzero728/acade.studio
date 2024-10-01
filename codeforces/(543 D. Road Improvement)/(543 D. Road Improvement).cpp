#include <bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 202020, mod = 1e9 + 7;

vector<int> adj[NN];

int dp[NN];

void dfs(int u) {
    dp[u] = 1;
    for(int v : adj[u]) {
        dfs(v);
        dp[u] = ((INT)dp[u] * (dp[v] + 1) % mod);
    }
}

void rdfs(int u, int up = 0) {
    int nn = adj[u].size();
    vector<int> L(nn), R(nn);
    for(int i = 0; i < nn; i++) {
        int v = adj[u][i];
        L[i] = R[i] = dp[v] + 1;
    }
    for(int i = 1; i < nn; i++) L[i] = (INT)L[i - 1] * L[i] % mod;
    for(int i = nn - 2; i >= 0; i--) R[i] = (INT)R[i + 1] * R[i] % mod;
    
    for(int i = 0; i < nn; i++) {
        int v = adj[u][i], Up = up + 1;
        if(0 <= i - 1) Up = (INT)Up * L[i - 1] % mod;
        if(i + 1 < nn) Up = (INT)Up * R[i + 1] % mod;
        dp[v] = (INT)dp[v] * (Up + 1) % mod;
        rdfs(v, Up);
    }
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 2; i <= n; i++) {
        int p; scanf("%d", &p);
        adj[p].push_back(i);
    }
    dfs(1);
    rdfs(1);
    
    for(int i = 1; i <= n; i++) printf("%d ", dp[i]);
    return 0;
}
