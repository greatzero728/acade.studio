#include<bits/stdc++.h>
using namespace std;


long long progress(int n, int m, long long d, const vector<int>& a, const vector<int>& b, const vector<int>& t) {
    deque<int> q;
    vector<vector<long long>> dp(2, vector<long long>(n + 1));
    int tag = 0;
    for (int i = 1; i <= m; ++i) {
        const vector<long long>& last = dp[tag];
        tag ^= 1;
        q.clear();
        int k = 1;
        long long dis = d * (t[i] - t[i - 1]);
        for (int j = 1; j <= n; ++j) {
            long long kTo = min(static_cast<long long>(n), j + dis);
            for (; k <= kTo; ++k) {
                while (!q.empty() && last[q.back()] <= last[k]) {
                    q.pop_back();
                }
                q.push_back(k);
            }
            long long kFrom = max(static_cast<long long>(1), j - dis);
            while (!q.empty() && q.front() < kFrom) {
                q.pop_front();
            }
            dp[tag][j] = last[q.front()] + b[i] - abs(j - a[i]);
        }
    }
    return *max_element(dp[tag].begin() + 1, dp[tag].end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long d;
    cin >> n >> m >> d;

    vector<int> a(m + 1), b(m + 1), t(m + 1);

    for (int i = 1; i <= m; ++i) {
        cin >> a[i] >> b[i] >> t[i];
    }

    cout << progress(n, m, d, a, b, t) << endl;

    return 0;
}