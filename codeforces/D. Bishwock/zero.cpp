#include<bits/stdc++.h>
using namespace std;

int n;
int dp[121][2][2];
char s[2][121];

int main() {
    scanf("%s %s", s[0] + 1, s[1] + 1);
    n = strlen(s[0] + 1);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                dp[i][j][k] = INT_MIN;
            }
        }
    }
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        char UL = s[0][i - 1], UR = s[0][i];
        char DL = s[1][i - 1], DR = s[1][i];
        
        if(UL == '0' && UR == '0' && DR == '0') dp[i][1][1] = max(dp[i][1][1], max(dp[i - 1][0][0], dp[i - 1][0][1]) + 1);
        if(DL == '0' && UR == '0' && DR == '0') dp[i][1][1] = max(dp[i][1][1], max(dp[i - 1][0][0], dp[i - 1][1][0]) + 1);

        if(UL == '0' && DL == '0' && DR == '0') dp[i][0][1] = max(dp[i][0][1], max({dp[i - 2][0][0], dp[i - 2][0][1], dp[i - 2][1][0], dp[i - 2][1][1]}) + 1);
        if(UL == '0' && DL == '0' && UR == '0') dp[i][1][0] = max(dp[i][1][0], max({dp[i - 2][0][0], dp[i - 2][0][1], dp[i - 2][1][0], dp[i - 2][1][1]}) + 1);
        
        dp[i][0][0] = max(dp[i][0][0], max({dp[i - 1][0][0], dp[i - 1][0][1], dp[i - 1][1][0], dp[i - 1][1][1]}));
    }
    
    printf("%d\n", max({dp[n][0][0], dp[n][0][1], dp[n][1][0], dp[n][1][1]}));
    return 0;
}