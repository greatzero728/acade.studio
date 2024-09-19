#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    int res = 0;
    vector<bool> t(n, false);

    for (int i = 0; i < m; ++i) {
        bool found = false;
        for (int j = 0; j < n - 1; ++j) {
            if (!t[j] && s[j][i] > s[j + 1][i]) {
                res++;
                found = true;
                break;
            }
        }
        if (!found) {
            for (int j = 0; j < n - 1; ++j) {
                t[j] = t[j] || (s[j][i] < s[j + 1][i]);
            }
        }
    }

    cout << res << endl;
    return 0;
}
