#include <bits/stdc++.h>
using namespace std;

constexpr int LOG = 17;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &u : a) cin >> u;
    vector<array<int, LOG>> spt(n);
    for (int i = 0; i < n; i++) spt[i][0] = a[i];
    for (int j = 1; j < LOG; j++)
        for (int bm = 1<<(j - 1), i = 0; i + (1<<j) <= n; i++)
            spt[i][j] = min(spt[i][j - 1], spt[i + bm][j - 1]);
    auto qry = [&] (int l, int r) {
        int p = 31 - __builtin_clz(r - l);
        return min(spt[l][p], spt[r - (1<<p)][p]);
    };
    for (int i = 0; i < n; i++) {
        int l = i, r = n;
        while (r - l > 1) {
            int g = (l + r) / 2;
            if (qry(g, n) < a[i]) l = g;
            else r = g;
        }
        cout << l - i - 1 << ' ';
    }
    return 0;
}