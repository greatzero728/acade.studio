#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> array(n);
    vector<vector<int>> positions(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
        positions[array[i]].push_back(i);
    }

    int total_segments = 0;
    int active_element1 = 0, active_element2 = 0;

    for (int i = 0; i < n; ++i) {
        ++total_segments;

        if (array[i] == active_element1 || array[i] == active_element2) {
            --total_segments;
            continue;
        }

        auto it1 = upper_bound(positions[active_element1].begin(), positions[active_element1].end(), i);
        auto it2 = upper_bound(positions[active_element2].begin(), positions[active_element2].end(), i);

        int next_pos1 = (it1 != positions[active_element1].end()) ? *it1 : n;
        int next_pos2 = (it2 != positions[active_element2].end()) ? *it2 : n;

        if (next_pos1 == n) {
            active_element1 = array[i];
        } else if (next_pos2 == n) {
            active_element2 = array[i];
        } else if (next_pos1 > next_pos2) {
            active_element1 = array[i];
        } else {
            active_element2 = array[i];
        }
    }

    cout << total_segments << "\n";

    return 0;
}