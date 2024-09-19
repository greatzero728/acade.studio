#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        long long m, n;
        cin >> m >> n;
        long long result = 1;
        for(int j = 1; j <= n; j++) {
            result = (result * m) % MOD;
        }
        long long sum = 0;
        for(long long p = 1; p * p <= result; p++) {
            if(result % p == 0) {
                sum += p;
                if(p * p != result) {
                    sum += result / p;
                }
            }
        }
        cout << "Case " << i << ": " << sum << endl;
    }
    return 0;
}