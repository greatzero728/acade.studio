#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        int p = 100;
        while (p <= 999) {
            int sumP = (p / 100) + ((p % 100) / 10) + (p % 10);
            int sumLastTwo = ((p - sumP) % 100) / 10 + ((p - sumP) % 10);
            if (sumLastTwo == n) {
                cout << "Case " << (i + 1) << ": " << (p - sumP) / 100 << endl;
                break;
            }
            p++;
        }
    }
    return 0;
}