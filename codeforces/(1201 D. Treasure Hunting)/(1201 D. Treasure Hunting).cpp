#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 3;
const long long INF = 1e18;
long long dp[N][2];
int L[N], R[N];
int main()
{
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    for (int i = 0; i <= n; i++)
        L[i] = 1e9, R[i] = -1e9;
    for (int i = 0; i < k; i++)
    {
        int r, c;
        cin >> r >> c;
        L[r] = min(L[r], c);
        R[r] = max(R[r], c);
    }
    vector<int> safe(q);
    for (int i = 0; i < q; i++)
        cin >> safe[i];
    sort(safe.begin(), safe.end());
    
    for (int i = 0; i <= n; i++)
        dp[i][0] = dp[i][1] = INF;
    dp[1][1] = R[1] - 1;
    
    int last = 1;
    for (int i = 2; i <= n; i++)
    {
        if (L[i] == 1e9)
            continue;
        auto update = [&](int pos, long long val)
        {
            dp[i][0] = min(dp[i][0], val + abs(R[i] - pos) + (R[i] - L[i]));
            dp[i][1] = min(dp[i][1], val + abs(L[i] - pos) + (R[i] - L[i]));
        };
        auto move = [&](int pos, long long val)
        {
            int index = lower_bound(safe.begin(), safe.end(), pos) - safe.begin();
            for (auto idx : {index, index - 1})
                if (idx >= 0 && idx < q)
                    update(safe[idx], val + abs(pos - safe[idx]) + (i - last));
        };
        move(L[last], dp[last][0]);
        move(R[last], dp[last][1]);
        last = i;
    }
}