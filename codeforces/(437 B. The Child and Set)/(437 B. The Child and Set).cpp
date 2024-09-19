#include <bits/stdc++.h>
using namespace std;

int main() {
    int s, l;
    cin >> s >> l;
    vector<int> r;

    while (l > 0 && s > 0) {
        if (s - (l & -l) >= 0) {
            s -= (l & -l);
            r.push_back(l);
        }
        l--;
    }

    if (s != 0) {
        cout << -1 << endl;
    } else {
        cout << r.size() << endl;
        for (int num : r) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
