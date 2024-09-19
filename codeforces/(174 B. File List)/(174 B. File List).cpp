#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> splits;
    for (int i = 0; i < n; i++) {
        if (s[i] == '.') {
            splits.push_back(i);
        }
    }
    if (splits.size() == 0) {
        cout << "NO" << endl;
        return 0;
    }
    if (splits[0] > 8 || splits[0] < 1) {
        cout << "NO" << endl;
        return 0;
    }
    if (n - splits.back() - 1 > 3 || n - splits.back() - 1 < 1) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 0; i < splits.size() - 1; i++) {
        int cnt = splits[i + 1] - splits[i] - 1;
        if (cnt > 11 || cnt < 2) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    int start = 0;
    for (int i = 0; i < splits.size(); i++) {
        if (i == splits.size() - 1) {
            cout << s.substr(start, n - start) << endl;
            break;
        }
        int cnt = splits[i + 1] - splits[i] - 1;
        cout << s.substr(start, splits[i] - start + min(3, cnt - 1) + 1) << endl;
        start = splits[i] + min(3, cnt - 1) + 1;
    }
    return 0;
}