#include "bits/stdc++.h"
using namespace std;
const int N = 5000 + 5;
int calc_for_two_rows[22][22];
int last_row_to_first[22][22];
int arr[22][10005];
int n, m;
int dp[22][22][1<<16];
int solve(int firstRow, int b4Row, int mask) {
    if (mask == (1 << n) - 1)
        return last_row_to_first[b4Row][firstRow];

    int &ret = dp[firstRow][b4Row][mask];
    if (~ret)
        return ret;

    for (int j = 0; j < n; j++) {
        if (!(mask >> j & 1)) {
            ret = max(ret, min(calc_for_two_rows[b4Row][j], solve(firstRow, j, mask | (1 << j))));
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j] ;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            calc_for_two_rows[i][j] = last_row_to_first[i][j] = INT_MAX;
            for (int k = 0; k < m; k++) {
                calc_for_two_rows[i][j] = min(calc_for_two_rows[i][j], abs(arr[i][k] - arr[j][k]));
            }
            for (int k = 0; k < m - 1; k++) {
                last_row_to_first[i][j] = min(last_row_to_first[i][j], abs(arr[i][k] - arr[j][k + 1]));
            }
        }
    }

    memset(dp, -1, sizeof dp);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, solve(i, i, 1 << i));
    }

    cout << ans << '\n';
    return 0;
}