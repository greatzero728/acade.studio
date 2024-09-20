#include<bits/stdc++.h>
using namespace std;
#define pb  push_back
#define ll  long long
#define vi  vector<ll >
#define vvi vector<vi >
#define all(x) x.begin(), x.end()

struct fenwick {
    int n;
    vector<int> t;
    fenwick(int n = 0) : n(n) {
        t.assign(n, 0);
    }
    void incr(int i, int delta) {
        for (; i < n; i |= (i + 1))
            t[i] += delta;
    }
    int sum(int r) {
        int s = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            s += t[r];
        return s;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

ll n, m;
vi a, b, p;

void rec(ll lb, ll rb, ll la, ll ra) {
    if (lb > rb) return;
    ll mb = (lb + rb) / 2;
    ll mi = 1e15;
    ll num = 0;
    for (int i = la; i < ra; ++i)
        num += (a[i] < b[mb]);
    for (ll pmb = la; pmb <= ra; ++pmb) {
        if (mi > num) {
            mi = num;
            p[mb] = pmb;
        }
        if (pmb == ra) continue;
        if (a[pmb] < b[mb]) --num;
        if (a[pmb] > b[mb]) ++num;
    }
    rec(lb, mb - 1, la, p[mb]);
    rec(mb + 1, rb, p[mb], ra);
}

ll f() {
    cin >> n >> m;
    a.resize(n);
    for (auto& x : a) cin >> x;
    b.resize(m);
    for (auto& x : b) cin >> x;
    sort(all(b));
    p.resize(m);
    rec(0, m - 1, 0, n);
    vi c; c.reserve(n + m);
    for (int i = 0, j = 0; i < n + 1; ++i) {
        while (j < m && p[j] == i)
            c.pb(b[j++]);
        if (i < n) c.pb(a[i]);
    }
    vi x = c;
    sort(all(x));
    x.resize(unique(all(x)) - x.begin());

    ll res = 0;
    fenwick F(x.size());
    for (auto& z : c) {
        z = lower_bound(all(x), z) - x.begin();
        res += F.sum(z + 1, x.size() - 1);
        F.incr(z, 1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--)
        cout << f() << "\n";

    return 0;
}