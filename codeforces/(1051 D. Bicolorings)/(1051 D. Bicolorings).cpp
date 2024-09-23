#include <bits/stdc++.h>
using namespace std;

long long const mod = 998244353;
int n, k;
long long dp[1001][2001][2]; 

long long sol(int i, int j, int flg) {
    if(i > n) return j == 0;
    long long &ret = dp[i][j][flg];
    if(ret != -1) return ret;

    ret = sol(i+1, j, flg);
    if(flg) {
        ret = (ret + 2 * sol(i + 1, j, !flg)) % mod;
        if(j >= 2) {
            ret = (ret + sol(i + 1, j - 2, flg)) % mod;
        }
    } else {
        ret = (ret + sol(i + 1, j - 1, flg)) % mod;
        ret = (ret + 2 * sol(i + 1, j - 1, !flg)) % mod;
    }

    return ret;
}

int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    memset(dp, -1, sizeof dp);

    long long ans = 0;

    ans = 2 * sol(2, k-1, 0);
    if(k >= 2) {
        ans = (ans + 2 * sol(2, k-2, 1)) % mod;
    }

    cout << ans << "\n";

    return 0;
}