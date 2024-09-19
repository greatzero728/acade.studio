#include <bits/stdc++.h>

using namespace std;

int val[1000000 + 10], x;

int bc(int n) {
    if (val[n ^ 1] == -1) {
        val[n] = 1;
        return 1;
    }
    return val[n] = bc(n / 2) ^ 1;
}

int main() {
    int h;
    cin >> h;
    for (int i = 0; i <= (1 << (h + 1)); i++) val[i] = -1;
    for (int i = 1; i < (1 << h); i++) {
        cin >> x;
        x += (1 << h);
        --x;
        cout << bc(x) << ' ';
    }
    cin >> x;
}