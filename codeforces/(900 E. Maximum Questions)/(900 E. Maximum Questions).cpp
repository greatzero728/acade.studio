#include <bits/stdc++.h>  

using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int m;
    cin >> m;
    vector<pair<int, int>> dp(n + 1);
    vector<vector<int>> prefa(n + 1, vector<int>(2));
    vector<vector<int>> prefb(n + 1, vector<int>(2));
    for (int i = 1; i <= n; i++) {
        prefa[i] = prefa[i - 1];
        prefb[i] = prefb[i - 1];
        if (s[i - 1] == 'a') prefa[i][i % 2]++;
        if (s[i - 1] == 'b') prefb[i][i % 2]++;
    }
    for (int i = m; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (prefa[i][(i - m) % 2] - prefa[i - m][(i - m) % 2] != 0) continue;
        if (prefb[i][(i - m + 1) % 2] - prefb[i - m][(i - m + 1) % 2] != 0) continue;
        int cost = m - (prefa[i][(i - m + 1) % 2] - prefa[i - m][(i - m + 1) % 2] + prefb[i][(i - m + 2) % 2] - prefb[i - m][(i - m + 2) % 2]);
        dp[i] = max(dp[i], make_pair(dp[i - m].first + 1, dp[i - m].second - cost));
    }
    cout << -dp[n].second << "\n";
    return 0;
}