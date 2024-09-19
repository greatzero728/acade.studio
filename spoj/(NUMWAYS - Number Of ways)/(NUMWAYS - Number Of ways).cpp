#include<bits/stdc++.h>

using namespace std;
using INT = long long;

const int NN = 1010101;

vector<int> adj[NN];

bool vst[NN];
INT dp[NN][4];
int cnt[NN], n, nn;

void dfs(int u) {
    vst[u] = 1, nn++;
    for(int v: adj[u]) {
        if(!vst[v]) dfs(v);
    }
}

int main() {
    int N, C; scanf("%d %d", &N, &C);
    while(C--) {
        int u, v; scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    for(int i = 1; i <= N; i++) if(!vst[i]) {
        nn = 0, dfs(i);
        cnt[++n] = nn;
    }
    
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 4; j--; ) dp[i][j] = dp[i - 1][j];
        for(int j = 1; j <= 3; j++) {
            dp[i][j] += dp[i - 1][j - 1] * cnt[i];
        }
    }
    
    cout << dp[n][3] << endl;
    return 0;
}
