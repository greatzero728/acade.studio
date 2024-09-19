#include <bits/stdc++.h>
#define y second
#define x first

using namespace std;

int n, m;
vector<int> strengths;
vector<pair<char, int>> actions;
int dp[21][1 << 20];

int solve(int i, int mask) {
    if(i == m) return 0;
    if(dp[i][mask] != -1) return dp[i][mask];
    int res = (actions[i].y == 1) ? -INT_MAX : INT_MAX;
    for(int j = 0; j < m; j++) if((mask & (1 << j)) != 0) {
        int new_mask = mask ^ (1 << j);
        int value;
        if(actions[i].x == 'p')
            value = (actions[i].y == 1 ? strengths[j] : -strengths[j]) + solve(i + 1, new_mask);
        else value = solve(i + 1, new_mask);
        res = (actions[i].y == 1) ? max(res, value) : min(res, value);
    }
    return dp[i][mask] = res;
}

int main() {
    scanf("%d", &n);
    strengths.resize(n);
    for(int i = n; i--; ) scanf("%d", &strengths[i]);
    
    sort(strengths.rbegin(), strengths.rend());
    scanf("%d", &m);
    
    actions.resize(m);
    for(int i = 0; i < m; i++) {
        scanf(" %c %d", &actions[i].x, &actions[i].y);
    }
    memset(dp, -1, sizeof dp);
    printf("%d\n", solve(0, (1 << m) - 1));
    return 0;
}