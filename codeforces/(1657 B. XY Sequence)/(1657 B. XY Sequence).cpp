#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, B, x, y;
        cin >> n >> B >> x >> y;
        long long sum = 0;
        long long curr = 0;
        for (int i = 0; i < n; i++) {
            if (curr + x <= B) {
                curr += x;
            } else {
                curr -= y;
            }
            sum += curr;
        }
        cout << sum << endl;
    }
    return 0;
}