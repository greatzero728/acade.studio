#include<iostream>
using namespace std;


void fastIO(void) {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
}

const int N = 1e6+5;
const int mod = 1e9 + 7;
const int Limit = 22;

int dp[N][Limit];
int Pr[N];

void preprocess(){

    for (int i = 0; i < N; ++i) {
        dp[i][0] = 1;
    }
    for (int i = 1; i < Limit; ++i) {
        dp[0][i] = 2;
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < Limit; ++j) {
            dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % mod;
        }
    }

    Pr[1] = 1;

    for (int i = 2; i < N; ++i) {
        if(!Pr[i]){
            for(int j = i; j < N; j += i){
                Pr[j] = i;
            }
        }
    }
}

int main(){
    fastIO();
    
    preprocess();
    int q;  cin >> q;
    while(q--){
        int r,n;  cin >> r >> n;
        int ans = 1;
        while(n != 1){
            int cnt = 0, p = Pr[n];
            while(n % p == 0){
                n /= p,cnt++;
            }
            ans = (ans * 1ll * dp[r][cnt]) % mod;
        }
        cout << ans << "\n";
    }

    return 0;
}