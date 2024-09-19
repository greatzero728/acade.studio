#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll MOD = 1e9 + 7;

ll powerMod(ll base, ll exp) {
    base %= MOD;
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) 
            result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result % MOD;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
    
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n + 1);
    vector<ll> dp(n + 1, 0);

    dp[0] = 1;  
    
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        for (ll j = i; j > 0; j--) {
            dp[j] = (dp[j] * a[i] % MOD - dp[j - 1] + MOD) % MOD;
        }
        dp[0] = dp[0] * a[i] % MOD;
    }
    
    ll result = 0;
    ll multiplier = 1;
    ll inv_n = powerMod(n, MOD - 2);
    
    for (ll i = 0; i <= n; i++) {
        result = (result + dp[i] * multiplier % MOD) % MOD;
        multiplier = multiplier * (k - i) % MOD * inv_n % MOD;
    }
    
    cout << (dp[0] - result + MOD) % MOD << endl;
    return 0;
}