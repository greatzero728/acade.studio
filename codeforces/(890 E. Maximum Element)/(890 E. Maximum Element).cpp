#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
const int mod = 1e9 + 7;

int my_pow(int n, int m) {
    if (m == 0) return 1;
    int res = my_pow(n, m / 2);
    res = (1LL * res * res) % mod;
    if (m % 2 == 1) res = (1LL * res * n) % mod;
    return res;
}

vector<int> fact;

int binom(int n, int k) {
    return ((1LL * fact[n] * my_pow(fact[n - k], mod - 2)) % mod * my_pow(fact[k], mod - 2)) % mod;
}

int main() {
    fact.resize(MAXN);
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) fact[i] = (1LL * i * fact[i - 1]) % mod;
    int n, k;
    cin >> n >> k;
    int ans = 0;
    vector<int> dp(n + 1);
    int sum = 0;
    for (int x = 1; x <= n; x++) {
        if (k + 1 >= x) continue;
        dp[x] = (1LL * (x - k - 1) * fact[x - 2]) % mod;
        dp[x] = (dp[x] + 1LL * fact[x - 2] * sum) % mod;
        sum = (sum - 1LL * dp[x - k] * my_pow(fact[x - k - 1], mod - 2)) % mod;
        if (sum < 0) sum += mod;
        sum = (sum + 1LL * dp[x] * my_pow(fact[x - 1], mod - 2)) % mod;
        ans = (ans + ((1LL * dp[x] * binom(n - 1, x - 1)) % mod) * fact[n - x]) % mod;
    }
    cout << ans << "\n";
    return 0;
}