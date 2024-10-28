#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

long long nCr(int n, int r, int p) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;

    vector<long long> fac(n + 1, 1);
    for (int i = 2; i <= n; ++i)
        fac[i] = fac[i - 1] * i % p;

    return fac[n] * power(fac[r], p - 2, p) % p * power(fac[n - r], p - 2, p) % p;
}

int main() {
    int n;
    cin >> n;

    long long beautifulArrays = (2 * nCr(2 * n - 1, n - 1, MOD) - n + MOD) % MOD;

    cout << beautifulArrays << endl;

    return 0;
}
