#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n, m, s;
    ll t;
    cin >> n >> m >> s >> t;
    
    vector<ll> stationVisit(n + 1, 0);
    
    for (ll currentT = t; currentT > 0; --currentT) {
        if (currentT % n == t % n) {
            if (stationVisit[s] != 0) {
                t = currentT % (stationVisit[s] - currentT);
                break;
            }
            stationVisit[s] = currentT;
        }
        
        if (s <= m) {
            s = (s + currentT - 1) % n + 1;
        } else {
            s = ((s - currentT) % n + n - 1) % n + 1;
        }
        
        if (currentT == 1) {
            cout << s;
            return 0;
        }
    }
    
    for (ll currentT = t; currentT > 0; --currentT) {
        if (s <= m) {
            s = (s + currentT - 1) % n + 1;
        } else {
            s = ((s - currentT) % n + n - 1) % n + 1;
        }
    }
    
    cout << s;
    return 0;
}