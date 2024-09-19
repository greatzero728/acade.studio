#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, p;
    cin >> n >> p;
    vector<string> s(n);
    vector<ll> a(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = n; i--; ) {
        if (s[i] == "halfplus") {
            a[i] = a[i + 1] * 2 + 1;
        } else {
            a[i] = a[i + 1] * 2;
        }
    }
    ll num = a[0], ans = 0;
    cout<<num<<endl;
    for (int i = 0; i < n; i++) {
        ll buy = num - num / 2;
        if (num % 2) buy++;
        ans += (buy - (num % 2)) * p;
        num /= 2 + (num % 2);
    }
    cout << ans << endl;
}