#include <iostream>
#include <vector>
#include <algorithm> // For sorting
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Sorting the array
    sort(a.begin(), a.end());

    // Calculating the sum
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i] * a[n - i - 1];
        sum %= 10007;  // Modulo operation to prevent overflow
    }

    cout << sum << endl;

    return 0;
}
