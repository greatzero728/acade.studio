#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<double>> a(1 << n, vector<double>(1 << n));
    vector<vector<double>> p(n + 1, vector<double>(1 << n));
    vector<vector<double>> e(n + 1, vector<double>(1 << n));
    for (auto &i: a)
        for (auto &j: i) cin >> j, j /= 100.0;
    p[0] = vector<double>(1 << n, 1);
    
    for (int r = 0; r < n; ++r) {
        for (int i = 0; i < (1 << n); ++i) {
            int groupi = i / (1 << r), groupj = groupi;
            if (groupi & 1) groupj--;
            else groupj++;
            for (int j = groupj * (1 << r); j < (groupj + 1) * (1 << r); ++j)
                p[r + 1][i] += p[r][j] * a[i][j];
            p[r + 1][i] *= p[r][i];
            for (int j = groupj * (1 << r); j < (groupj + 1) * (1 << r); ++j)
                e[r + 1][i] = max(e[r + 1][i], e[r][i] + e[r][j] + p[r + 1][i] * (1 << r));
        }
    }
    double ans{};
    for (int i = 0; i < (1 << n); ++i)
        ans = max(ans, e[n][i]);
    cout << setprecision(10) << ans << '\n';
}