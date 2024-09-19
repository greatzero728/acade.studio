#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
pair<int, int> a[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, a[i].first + a[i].second);
    }
    cout << ans << endl;
    return 0;
}