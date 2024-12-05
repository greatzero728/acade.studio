#include <bits/stdc++.h>

using namespace std;

const int NN = 121;

bool adj[NN][NN], flag[NN][NN];

int solve() {
    int N; scanf("%d", &N);
    memset(adj, 0, sizeof adj);
    memset(flag, 0, sizeof flag);
    for(int i = 0; i < N; i++) {
        int a, b; scanf("%d %d", &a, &b);
        adj[a][b] = 1;
        flag[a][b] = 1;
    }
    for(int k = 0; k < N; k++) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(adj[i][k] && adj[k][j]) adj[i][j] = 1;
            }
        }
    }
    int cnt = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(adj[i][j] && !flag[i][j]) cnt++;
        }
    }
    return cnt;
}

int main() {
    int T; scanf("%d", &T);
    for(int i = 1; i <= T; i++) printf("Case #%d: %d\n", i, solve());
}