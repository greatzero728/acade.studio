#include<bits/stdc++.h>
using namespace std;
const int mod = 7340033;
void square(vector<long long> &poly) {
    vector<long long> ans(1010);
    for(int i = 0 ; i < ans.size(); i++){
        for(int j = 0; j <= i; j++){
            int k = i - j;
            if(k < poly.size()){
                ans[i] += poly[j] * poly[k] % mod;
                ans[i] %= mod;
            }
        }
    }
    poly = ans;
}

int main(){
    int q;
    cin >> q;
    vector<vector<long long>> dp(31, vector<long long>(1010));
    dp[0] = {1};
    dp[1] = {1, 1};
    for(int i = 2; i < 31; i++){
        dp[i] = dp[i-1];
        square(dp[i]);
        square(dp[i]);
        for(int j = 1009; j >= 1; j--){
            dp[i][j] = dp[i][j - 1];
        }
        dp[i][0] = 1;
    }
    while(q--){
        int n, k;
        cin >> n >> k;
        int v = 0;
        while(n > 1 && (n & 1)){
            n >>= 1;
            v++;
        }
        cout << dp[v][k] << endl;
    }
}