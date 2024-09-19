#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), greater<int>());  // Sort in descending order
    
    int l = 1, r = n;

    while (l < r) {
        int x = (l + r) / 2;
        long long t = 0;

        for (int i = 0; i < n; ++i) {
            t += max(a[i] - i / x, 0);
        }

        if (t < m) {
            l = x + 1;
        } else {
            r = x;
        }
    }

    if (l == n && accumulate(a.begin(), a.end(), 0LL) < m) {
        cout << -1 << endl;
    } else {
        cout << l << endl;
    }

    return 0;
}
