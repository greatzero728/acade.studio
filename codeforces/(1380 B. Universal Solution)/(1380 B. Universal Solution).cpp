#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int r = 0, p = 0, sc = 0;
        for (int i = 0; i < s.size(); i++) {
            switch (s[i]) {
                case 'R':
                    r++;
                    break;
                case 'S':
                    sc++;
                    break;
                case 'P':
                    p++;
                    break;
            }
        }
        if (r >= p && r >= sc) {
            for (int i = 0; i < s.size(); i++)
                cout << "P";
        } else if (p >= r && p >= sc) {
            for (int i = 0; i < s.size(); i++)
                cout << "S";
        } else {
            for (int i = 0; i < s.size(); i++)
                cout << "R";
        }
        cout << endl;
    }
    return 0;
}