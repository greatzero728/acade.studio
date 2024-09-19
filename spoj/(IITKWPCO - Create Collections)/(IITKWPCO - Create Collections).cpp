#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> numbers(n);
        for (int i = 0; i < n; i++) {
            cin >> numbers[i];
        }
        sort(numbers.begin(), numbers.end());
        int collections = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (numbers[j] == 2 * numbers[i]) {
                    collections++;
                    numbers[i] = -1;
                    numbers[j] = -1;
                    break;
                }
            }
        }
        cout << collections << endl;
    }
    return 0;
}