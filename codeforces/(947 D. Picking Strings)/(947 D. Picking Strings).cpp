#include <bits/stdc++.h>
using namespace std;

int nonA_S[100003], nonA_T[100003], maxA_S[100003], maxA_T[100003];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    string s, t;
    cin >> s >> t;

    for (int i = 0; i < s.size(); i++) {
        nonA_S[i + 1] = nonA_S[i] + (s[i] != 'A');
        maxA_S[i + 1] = (s[i] == 'A' ? maxA_S[i] + 1 : 0);
    }

    for (int i = 0; i < t.size(); i++) {
        nonA_T[i + 1] = nonA_T[i] + (t[i] != 'A');
        maxA_T[i + 1] = (t[i] == 'A' ? maxA_T[i] + 1 : 0); 
    }

    int numQueries;
    cin >> numQueries;

    string result;

    while (numQueries--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; c--;
        
        int nonA_S_count = nonA_S[b] - nonA_S[a];
        int nonA_T_count = nonA_T[d] - nonA_T[c]; 

        int maxA_S_count = min(maxA_S[b], b - a);
        int maxA_T_count = min(maxA_T[d], d - c);

        if (nonA_S_count > nonA_T_count || (nonA_S_count % 2 != nonA_T_count % 2) || 
            maxA_S_count < maxA_T_count || 
            (nonA_S_count == nonA_T_count && maxA_S_count % 3 != maxA_T_count % 3) || 
            (nonA_S_count == 0 && nonA_T_count > 0 && maxA_S_count == maxA_T_count)) {
            result += '0';
        } else {
            result += '1';
        }
    }

    cout << result;
}
