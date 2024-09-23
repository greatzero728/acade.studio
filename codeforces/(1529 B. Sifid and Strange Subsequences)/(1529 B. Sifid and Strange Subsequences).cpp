#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int ans = 1;
        int min_diff = 1e9;
        for (int i = 1; i < n; i++) {
            if (a[i] - a[i - 1] < min_diff) {
                min_diff = a[i] - a[i - 1];
            }
            if (min_diff >= a[i]) {
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}