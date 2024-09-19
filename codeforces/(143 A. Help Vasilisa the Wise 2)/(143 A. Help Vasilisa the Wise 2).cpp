#include <iostream>
using namespace std;

int main() {
    int r1, r2, c1, c2, d1, d2;
    cin >> r1 >> r2 >> c1 >> c2 >> d1 >> d2;

    int a, b, c, d;
    bool found = false;

    for (a = 1; a <= 9; a++) {
        for (b = 1; b <= 9; b++) {
            if (a + b != r1) continue;
            if (a == b) continue;
            for (c = 1; c <= 9; c++) {
                if (c == a || c == b) continue;
                for (d = 1; d <= 9; d++) {
                    if (d == a || d == b || d == c) continue;
                    if (c + d != r2) continue;
                    if (a + c != c1) continue;
                    if (b + d != c2) continue;
                    if (a + d != d1) continue;
                    if (b + c != d2) continue;
                    cout << a << " " << b << endl;
                    cout << c << " " << d << endl;
                    found = true;
                    break;
                }
                if (found) break;
            }
            if (found) break;
        }
        if (found) break;
    }

    if (!found) cout << -1 << endl;

    return 0;
}