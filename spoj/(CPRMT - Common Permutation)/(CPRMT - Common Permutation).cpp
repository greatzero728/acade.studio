#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    while (cin >> a >> b) {
        unordered_map<char, int> freq_a, freq_b;
        for (char c : a) freq_a[c]++;
        for (char c : b) freq_b[c]++;
        string result;
        for (char c = 'a'; c <= 'z'; c++) {
            for (int i = 0; i < min(freq_a[c], freq_b[c]); i++) {
                result += c;
            }
        }
        cout << result << endl;
    }
    return 0;
}