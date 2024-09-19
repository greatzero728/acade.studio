#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 5;
int n;
int a[maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    int m = unique(a + 1, a + n + 1) - a - 1;
    int ans = 0;
    int dp[1000005];
    for (int i = 0; i < 1000005; i++)
        dp[i] = 0;
    for (int i = 1; i <= m; i++)
        dp[a[i]] = a[i];
    for (int i = 1; i <= 1000000; i++)
        dp[i] = max(dp[i], dp[i - 1]);
    for (int i = 1; i <= m; i++) {
        int j = 1;
        while (a[i] * j <= 1000000) {
            ans = max(ans, dp[min(1000000, a[i] * j + a[i] - 1)] - a[i] * j);
            j++;
        }
    }
    printf("%d\n", ans);
}