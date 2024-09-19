#include <bits/stdc++.h>
using namespace std;
#define double long double
int main() {
    int n, l, v1, v2;
    cin >> n >> l >> v1 >> v2;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    double d = (double)(v2) / (double)(v1 + v2)*l;

    vector<pair<double, int>> w;
    w.push_back({0, 0});
    int num_of_chocolates=0;
    for (int i = 0; i < n; i++) {
        if (a[i] - d < 0) {
            w.push_back({2ll*l + a[i] - d, 1});
            num_of_chocolates++;
        }
        else w.push_back({a[i] - d, 1});
        w.push_back({a[i], -1});
    }
    w.push_back({2ll*l, 0});
    sort(w.begin(), w.end());

    vector<double> ans(n + 1,0);
    num_of_chocolates += w[0].second;
    for (int i = 1; i < w.size(); i++) {
        ans[num_of_chocolates] += w[i].first - w[i - 1].first;
        num_of_chocolates += w[i].second;
    }

    for (int i = 0; i <= n; i++) {
        cout << fixed << setprecision(10) << ans[i] / (2ll * l) << '\n';
    }
    
    return 0;
}