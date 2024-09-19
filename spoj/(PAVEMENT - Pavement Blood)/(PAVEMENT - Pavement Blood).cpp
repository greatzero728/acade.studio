#include <bits/stdc++.h>

using namespace std;
using INT = long long;

const int N = 101010;

INT a[N][5];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 3; j++) cin >> a[i][j];
    }

    INT dp[n + 1];
    dp[0] = 0;
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = max(dp[i - 1], max(dp[i - 2] + a[i - 1][1] + a[i - 1][2] + a[i][1] + a[i][2], dp[i - 2] + a[i - 1][2] + a[i - 1][3] + a[i][2] + a[i][3]));
    }

    cout << dp[n];

    return 0;
}