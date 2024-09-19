#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

long long exp(long long base, long long power, long long mod) {
    long long result = 1;
    base = base % mod;
    while (power > 0) {
        if (power & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        power = power >> 1;
    }
    return result;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << exp(2, n - 1, MOD) << endl;
    }
    return 0;
}