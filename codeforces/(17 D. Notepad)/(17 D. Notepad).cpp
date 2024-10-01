#include <bits/stdc++.h>

using namespace std;

#define int long long

int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            res -= res / i;
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

int modExp(int base, int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string strB, strN;
    int c;
    cin >> strB >> strN >> c;
    int b = 0, n = 0;int mod = phi(c);bool flag = 0;
    for (int i = strN.size()-1; i >= 0; --i)if(strN[i]=='0')strN[i]='9';else{strN[i]--;break;}
    for (int i = 0; i < strB.size(); ++i) b = (b * 10 + strB[i] - '0') % c;
    for (int i = 0; i < strN.size(); ++i)flag |= (n * 10 + strN[i] - '0') >= mod, n = (n * 10 + strN[i] - '0') % (mod);
    if(flag)n += mod;
    if(!b)b=c;
    int ans = modExp(b, n , c) * (b - 1) % c;
    if(ans == 0)ans = c;
    cout << ans << endl;
}