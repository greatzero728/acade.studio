#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int idx[n];
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            idx[x - 1] = i;
        }
        int mn = n, mx = 0;
        for (int i = 0; i < n; i++) {
            mn = min(idx[i], mn);
            mx = max(idx[i], mx);
            if (mx - mn == i) cout << 1;
            else cout << 0;
        }
        cout << '\n';
    }
    
    return 0;
}