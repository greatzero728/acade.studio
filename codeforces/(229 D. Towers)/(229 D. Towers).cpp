#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
int h[N], pf[N], dp[N], lst[N];

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    for (int i = 1; i <= n; i++)
    {
        pf[i] = pf[i - 1] + h[i], dp[i] = n;
        for (int j = i - 1; j >= 0; j--)
            if (pf[i] - pf[j] >= lst[j] && dp[j] + i - j - 1 < dp[i])
                dp[i] = dp[j] + i - j - 1, lst[i] = pf[i] - pf[j];
    }
    cout << dp[n] << '\n';
}