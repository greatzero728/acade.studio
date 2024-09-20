#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll f(ll n, int bits, int j) {
    ll res = 0;
    for (int i = 1; i <= j; ++i) {
        if (n & (1ll << (bits - i)))
            res += (1ll << (j - i));
    }
    ll val = res;
    for (int i = 1; i < bits / j; i++) {
        val <<= j;
        val += res;
    }
    res = res - (1ll << (j - 1));
    if (val <= n)
        res++;
    return res;
}

ll calc(ll n) {
    int bits = __lg(n) + 1;
    ll res = 0;
    for (int i = 1; i <= bits; ++i) {
        vector<ll> ans(bits + 1, 0);
        for (int j = 1; j <= i / 2; ++j) {
            if (i % j == 0) {
                if (i < bits) {
                    ans[j] += (1ll << (j - 1));
                } else {    
                    ans[j] += f(n, bits, j);
                }
                for (int k = 1; k < j; ++k) {
                    if (j % k == 0)
                        ans[j] -= ans[k];
                }
                res += ans[j];
            }
        }
    }
    return res;
}

int main(){
    ll a, b;
    cin >> a >> b;
    cout << calc(b) - calc(a - 1) << endl;
}