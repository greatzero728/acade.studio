#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main() {
    ll n;
    cin >> n;
    map<ll, vector<ll>> mp;
    for(ll i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        mp[a].push_back(b);
        mp[b].push_back(a);
    }
    
    ll beg = -10, cur = -10;
    for(auto a: mp) {
        if(a.second.size() == 1) {
            beg = a.first;
            cout << beg << " ";
            cur = a.second[0];
            break;
        }
    }
    while(true) {
        cout << cur << " ";
        if(mp[cur].size() == 1) {
            break;
        }
        if(mp[cur][0] == beg) {
            beg = cur;
            cur = mp[cur][1];
        }
        else {
            beg = cur;
            cur = mp[cur][0];
        }
    }
    return 0;
}