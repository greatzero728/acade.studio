#include <bits/stdc++.h>
using namespace std;

int main() {
    string input;
    getline(cin, input);
    
    vector<char> s(input.begin(), input.end());
    
    int r = s.size() / 20 + (s.size() % 20 != 0);
    int c = s.size() / r + (s.size() % r != 0);
    
    for (int i = 0; i < (r - s.size() % r) % r; ++i) {
        s.insert(s.begin() + c * i, '*');
    }
    
    cout << r << " " << c << endl;
    
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (c * i + j < s.size()) {
                cout << s[c * i + j];
            }
        }
        cout << endl;
    }
    
    return 0;
}
