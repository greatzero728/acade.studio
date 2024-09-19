#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool can(int i , vector<ll>&v) {
    bool c1 = false , c2 = false;
    for(auto &val:v) {
        if(!(val & (1LL<<i)))c1 = true;
        else c2 = true;
    }
    return c1 && c2;
}
int main() {
    int n;cin>>n;
    ll ans = 0;
    vector<ll>v(n);
    for(auto &val:v)cin>>val;
    for(int i = 0;i < 63;i++) {
        if(can(i , v)) {
            ans |= (1LL<<i);
        }
    }
    cout<<ans<<endl;
}