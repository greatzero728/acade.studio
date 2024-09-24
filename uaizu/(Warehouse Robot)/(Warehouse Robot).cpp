#include<bits/stdc++.h>
using namespace std;

void solve() {
    int x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;
    if (x0 > x1) {
        x0 = 301 - x0;
        x1 = 301 - x1;
    }
    if (y0 > y1) {
        y0 = 301 - y0;
        y1 = 301 - y1;
    }
    vector<vector<double>> dp(302, vector<double>(302, 10000));
    dp[y0][x0] = 0;
    for (int y = y0; y <= y1; y++) {
        for (int x = x0; x <= x1; x++) {
            double min_len = 10000;
            for (int j = 0; j < 301; j++) {
                if (y - j >= 0)
                    min_len = min(min_len, dp[y - j][x] + j);
            }
            if (x % 2 == 0 && x > 0) {
                for (int j = 0; j < 301; j++) {
                    if (y - j >= 0)
                        min_len = min(min_len, dp[y - j][x - 1] + sqrt(j * j + 1));
                }
            }
            for (int j = 0; j < 301; j++) {
                if (x - j >= 0)
                    min_len = min(min_len, dp[y][x - j] + j);
            }
            if (y % 2 == 0 && y > 0) {
                for (int j = 0; j < 301; j++) {
                    if (x - j >= 0)
                        min_len = min(min_len, dp[y - 1][x - j] + sqrt(j * j + 1));
                }
            }
            
            dp[y][x] = min_len;
        }
    }
    cout<<setprecision(6);
    cout <<fixed<<dp[y1][x1] << endl;
}

int main() {
    solve();
    return 0;
}