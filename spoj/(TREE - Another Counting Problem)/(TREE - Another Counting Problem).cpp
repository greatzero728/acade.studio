#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
 
using namespace std;
using namespace boost::multiprecision;
 
cpp_int power(cpp_int a, cpp_int b) {
    cpp_int ans = 1;
    while(b--) ans *= a;
    return ans;
}

cpp_int dp[33] = {1};

int main() {
    int n, d;
    while(~scanf("%d %d", &n, &d)) {
        if(n == 0 && d == 0) return 0;
        
        printf("%d %d ", n, d);
        
        if(d > 0) {
            dp[0] = 1;
            for(int i = 1; i <= d; i++) dp[i] = 1 + power(dp[i - 1], n);
            cout<<dp[d] - dp[d - 1]<<endl;
        }
        else puts("1");
    }
}