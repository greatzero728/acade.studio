#include <bits/stdc++.h>
using namespace std;

constexpr int N = 4e6 + 1;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, x;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; a[i] += a[i - 1]; }
    for (int i = 1; i <= m; i++) { cin >> b[i]; b[i] += b[i - 1]; }
    cin >> x;
    vector<int> sb(N);
    for (int i = 1; i <= m; i++)
        for (int j = 0; j < i; j++)
            sb[b[i] - b[j]] = max(sb[b[i] - b[j]], i - j);
    for (int i = 1; i < N; i++) sb[i] = max(sb[i], sb[i - 1]);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            int sa = a[i] - a[j];
            ans = max(ans, sb[min(N - 1, x / sa)] * (i - j));
        }
    }
    cout << ans;
    return 0;
}