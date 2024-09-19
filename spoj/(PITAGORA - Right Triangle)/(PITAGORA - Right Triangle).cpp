#include <iostream>
#include <cmath>

using namespace std;

void solve(int n) {
    int m = 0;
    int k = 0;

    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            int j = n / i;
            if ((i + j) % 2 == 0 && (j - i) % 2 == 0) {
                m = (i + j) / 2;
                k = (j - i) / 2;
                break;
            }
        }
    }

    int b = 2 * m * k;
    int c = m * m + k * k;

    cout << n << " " << b << " " << c << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    while(cin >> n) {solve(n);}

    return 0;
}