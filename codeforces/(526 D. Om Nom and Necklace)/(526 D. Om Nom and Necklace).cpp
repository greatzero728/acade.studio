#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
long long n, k;
long long b[N];
string s;
int main() {
    cin >> n >> k >> s;
    
    int i = 0, j = -1;
    b[0] = -1;
    while (i < n) {
        while (j >= 0 && s[i] != s[j])j = b[j];
        i++, j++;
        b[i] = j;
        int len = i - b[i];
        int tot = i / len;
        int x = tot / k;
        int y = i - x * len * k;
        if (x * len >= y)cout << 1;
        else cout << 0;
    }
    return 0;
}