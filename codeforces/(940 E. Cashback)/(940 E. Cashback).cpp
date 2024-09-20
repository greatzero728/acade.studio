#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main(){
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<ll> dp(n+5, 0);
    multiset<int> st;
    ll sum = 0;
    for (int i = n-1; i >= 0; --i) {
        dp[i] = dp[i+1]+a[i];
        st.insert(a[i]);
        sum += a[i];
        if(st.size() > c){
            st.erase(st.find(a[i+c]));
            sum -= a[i+c];
        }
        if(st.size() == c){
            ll newSum = sum-*st.begin();
            dp[i] = min(dp[i], newSum + dp[i+c]);
        }
    }
    cout << dp[0] << endl;
}