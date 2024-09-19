#include <bits/stdc++.h>

#define ll long long
using namespace std;

int main() {
    ll n, m, b;
    cin >> n >> m >> b;
    array<ll, 3> a[n];
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> a[i][0] >> a[i][1] >> x;
        a[i][2] = 0;
        for (int j = 0; j < x; ++j) {
            int y;
            cin >> y;
            y--;
            a[i][2] |= (1 << y);
        }
    }
    sort(a, a + n, [](auto a, auto b) { return a[1] < b[1]; });

    const ll INF = (1LL << 62);
    ll dp[1 << (m + 1)];
    fill(dp, dp + (1 << m), INF);

    ll ans = INF;
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 1 << m; ++j) {
            dp[j | a[i][2]] = min(dp[j | a[i][2]], dp[j] + a[i][0]);
        }
        ans = min(ans, dp[(1 << m) - 1] + a[i][1] * b);
    }
    if (ans == INF)
        cout << -1 << endl;
    else
        cout << ans << endl;
}