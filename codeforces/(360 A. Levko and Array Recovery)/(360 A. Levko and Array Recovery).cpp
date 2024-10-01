#include <bits/stdc++.h>
using namespace std;

struct operatoin {
    int type, l, r, d;
};

signed main() {
    int n, m;
    cin >> n >> m;
    vector<operatoin> ope(m);
    for(int i = 0; i < m; i++) {
        cin >> ope[i].type >> ope[i].l >> ope[i].r >> ope[i].d;
    }
    vector<int> ds(n+1), a(n+1, 1e9);
    for(auto &p : ope) {
        if(p.type == 1) {
            for(int i = p.l; i <= p.r; i++) {
                ds[i] += p.d;
            }
        } else {
            for(int i = p.l; i <= p.r; i++) {
                a[i] = min(a[i], p.d-ds[i]);
            }
        }
    }
    ds = vector<int>(n+1);
    for(auto &p : ope) {
        if(p.type == 1) {
            for(int i = p.l; i <= p.r; i++) {
                ds[i] += p.d;
            }
        } else {
            int mx = INT_MIN;
            for(int i = p.l; i <= p.r; i++) {
                mx = max(mx, a[i]+ds[i]);
            }
            if(mx != p.d) {
                cout << "NO";
                return 0;
            }
        }
    }
    cout << "YES\n";
    for(int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
}   