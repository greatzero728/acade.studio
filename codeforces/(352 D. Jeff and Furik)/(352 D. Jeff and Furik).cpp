#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    int inversions = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] > p[j]) {
                inversions++;
            }
        }
    }

    double expected_moves = 2 * inversions;
    if (inversions % 2 != 0) {
        expected_moves--;
    }
    cout << fixed << expected_moves << endl;
    return 0;
}