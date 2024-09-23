#include <bits/stdc++.h>

using namespace std;

const int NN = 101010;
const int mod = 998244353;

int powmod(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = (1LL * res * a) % mod;
        a = (1LL * a * a) % mod;
        b >>= 1;
    }
    return res;
}

int inv(int a) {
    return powmod(a, mod - 2);
}

int C(int n, int k) {
    if(n < k) return 0;
    int res = 1;
    for(int i = 1; i <= k; i++) {
        res = (1LL * res * (n - i + 1)) % mod;
        res = (1LL * res * inv(i)) % mod;
    }
    return res;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        char s[NN]; scanf("%s", s);
        int p = 0, e = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '0') e++;
            else if(i + 1 < n && s[i + 1] == '1') {
                p++;
                i++;
            }
        }
        printf("%d\n", C(e + p, p));
    }
}