#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
const int MAXA = 4e5 + 10;

int n;
int b[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    long long ans = 0;
    vector<long long> a(MAXA + MAXN);
    for (int i = 1; i <= n; i++) {
        a[b[i] - i + MAXN] += b[i];
    }
    for (int i = 0; i < MAXA + MAXN; i++) {
        ans = max(ans, a[i]);
    }
    cout << ans;

    return 0;
}