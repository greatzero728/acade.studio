#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> l(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i];
    }
    
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        ans += min(l[x - 1], l[y - 1]);
    }
    
    cout << ans << endl;

    return 0;
}
