#include <bits/stdc++.h>

using namespace std;

const int NN = 121;

char x[NN];
vector<string> ans;

int dp[NN], n;

void dfs(int i, string cur) {
    if(!i) {
        ans.push_back(cur);
        return;
    }
    for(int j = 0; j < i; j++) {
        if(x[j] <= x[i] && dp[i] == dp[j] + 1) {
            dfs(j, x[i] + cur);
        }
    }
}

void solve() {
    scanf("%s", x + 1);
    n = strlen(x + 1);
    for(int i = 0; i <= n; i++) {
        dp[i] = 1;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            if(x[i] >= x[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int mx = 0;
    for(int i = 0; i <= n; i++) {
        mx = max(mx, dp[i]);
    }
    ans.clear();
    for(int i = n; i >= 1; i--) {
        if(dp[i] == mx) {
            dfs(i, "");
        }
    }
    sort(ans.begin(), ans.end());
    for(string v: ans) {
        printf("%s\n", v.c_str());
    }
    puts("");
}

int main() {
    int t; scanf("%d", &t);
    while(t--) solve();
    return 0;
}