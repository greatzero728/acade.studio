#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, p, k;
    cin >> n >> p >> k;
    
    vector<vector<int>> v(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        cin >> v[i][0]; // Assuming input for the first value
        cin >> v[i][1]; // Assuming input for the second value
        v[i].push_back(i); // Add index
    }

    // Sort based on the second element, then by first (descending)
    sort(v.begin(), v.end(), [](const vector<int>& a, const vector<int>& b) {
        return (a[1] < b[1]) || (a[1] == b[1] && a[0] > b[0]);
    });

    vector<vector<int>> v2;
    for (int i = p - k; i < n; ++i) {
        v2.push_back(v[i]);
    }

    // Sort v2 based on the first element and index (descending)
    sort(v2.begin(), v2.end(), [](const vector<int>& a, const vector<int>& b) {
        return (a[0] > b[0]) || (a[0] == b[0] && a[2] > b[2]);
    });

    int min_id = n + 1;
    for (int i = 0; i < k; ++i) {
        cout << v2[i][2] + 1 << " ";
        min_id = min(min_id, v2[i][3]);
    }

    for (int i = min_id - (p - k); i < min_id; ++i) {
        cout << v[i][2] + 1 << " ";
    }

    return 0;
}
