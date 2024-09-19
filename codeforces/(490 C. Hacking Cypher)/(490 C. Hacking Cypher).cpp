#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    int a, b;
    cin >> s >> a >> b;

    int n = s.length();
    int pref[n];
    int suff[n];

    int rem = (s[0] - '0') % a;
    pref[0] = rem;
    for(int i = 1 ; i < n ; i++) {
        rem = (rem * 10 + s[i] - '0') % a;
        pref[i] = rem;
    }

    int curr = 1;
    suff[n-1] = rem = (s[n-1] - '0') % b;
    for(int i = n-2 ; i >= 0 ; i--) {
        curr = (curr * 10) % b;
        rem = ((s[i]-'0')*curr + rem) % b;
        suff[i] = rem;
    }

    bool found = false;
    for(int i = 1 ; i < n ; i++) {
        if( pref[i-1] == 0 && suff[i] == 0 && s[i] != '0') {
            cout << "YES" << endl;
            cout << s.substr(0, i) << endl;
            cout << s.substr(i, n-i) << endl;
            found = true;
            break;
        }
    }

    if(!found)
        cout << "NO" << endl;

    return 0;
}