#include <bits/stdc++.h>

using namespace std;

const int MAX_TIME_SLOT = 16;
const int MAX_N = 100;
const int INF = 1e9;

int N;
int M[MAX_N];
int L[MAX_N];
int S[MAX_N][MAX_TIME_SLOT];
int E[MAX_N][MAX_TIME_SLOT];
int bitmasks[MAX_N];

int dp[MAX_N + 1][1 << MAX_TIME_SLOT];

int main() {
    while(~scanf("%d", &N) && N) {
        for(int i = 0; i < N; i++) {
            scanf("%d %d", &M[i], &L[i]);
            for(int j = 0; j < M[i]; j++) {
                scanf("%d %d", &S[i][j], &E[i][j]);
                S[i][j] -= 6;
                E[i][j] -= 6;
            }
        }
        for(int i = 0; i < N; i++) {
            bitmasks[i] = 0;
            for(int j = 0; j < M[i]; j++) {
                for(int k = S[i][j]; k < E[i][j]; k++) {
                    bitmasks[i] |= (1 << k);
                }
            }
        }
        memset(dp, -1, sizeof dp);
        dp[0][0] = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < (1 << MAX_TIME_SLOT); j++) {
                if(dp[i][j] != -1) {
                    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                    if((j & bitmasks[i]) == 0) {
                        dp[i + 1][j | bitmasks[i]] = max(dp[i + 1][j | bitmasks[i]], dp[i][j] + L[i]);
                    }
                }
            }
        }
        int ans = 0;
        for(int j = 0; j < (1 << MAX_TIME_SLOT); j++) {
            ans = max(ans, dp[N][j]);
        }
        printf("%d\n", ans);
    }
}