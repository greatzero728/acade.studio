#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        bool good = true;
        for (int j = 0; j <= k; ++j) {
            char c = '0' + j;
            if (a[i].find(c) == string::npos) {
                good = false;
                break;
            }
        }
        if (good) ++ans;
    }
    cout << ans << endl;
    return 0;
}