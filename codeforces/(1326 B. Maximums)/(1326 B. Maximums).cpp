#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> b(n), a(n);
    for (auto &u : b) cin >> u;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        a[i] = b[i] + mx;
        mx = max(mx, a[i]);
    }
    for (auto u : a) cout << u << ' ';
    return 0;
}