#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    int t, Case = 1; cin >> t;
    ll sum = 0, ans = 0, mn  =0;
    while(t--) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        sum = (a + b + c + d);
        mn = min({sum - a, sum - b, sum  - c, sum - d});
        ans = min(mn, sum / 4);
        cout << "Case " << Case << ": " << ans << endl;
        Case++;
    }
    return 0;
}
