#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll q, b, a, o, u;
    while (cin >> q) {
        if(q==0)break;
        cin >> b >> a >> o >> u;
        ll xans=0, yans=0;
        for (ll x = 1; x*a<= b && x <= u; x++) {
            ll y = (b - x * a) / o;
            if (x + y >= q && x*a+y*o<=b) {
                xans = x;
                yans = y;
            }
        }
        if (xans == 0) {
            cout << "NA" << endl;
        } else {
            cout << xans << " " << yans << endl;
        }
    }
    return 0;
}