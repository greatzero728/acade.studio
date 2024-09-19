#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] % a[n - 1] == 0) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}