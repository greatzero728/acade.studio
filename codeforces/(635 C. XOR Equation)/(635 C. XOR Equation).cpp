#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll s, x;
    cin >> s >> x;
    if ((s < x) || (s%2 != x%2)) return cout << 0, 0;
    ll d = (s - x) / 2;
    if (d & x) return cout << 0, 0;
    ll ans = 1;
    for (int i = 0; i < 60; i++) {
        if (d & (1LL << i)) continue;
        if (x & (1LL << i)) ans *= 2;
    }
    if (!d) ans -= 2;
    cout << ans;
    return 0;
}
