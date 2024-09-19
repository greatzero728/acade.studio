#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int n, k;
    cin >> n >> k;
    int g = k;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        g = gcd(g,x);
    }
    cout << k / g << endl;
    for (int i = 0; i < k; i += g) {
        cout << i << " ";
    }
    cout << endl;
}