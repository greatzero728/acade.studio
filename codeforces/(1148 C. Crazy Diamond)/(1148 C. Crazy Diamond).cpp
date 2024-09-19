#include<bits/stdc++.h>

using namespace std;

const int N = 300005;

int n;
int a[N], pos[N];

vector<pair<int, int>> ans;

void doSwap(int i, int j) {

    ans.push_back({i, j});
    swap(pos[a[i]], pos[a[j]]);
    swap(a[i], a[j]);

}

void swap_operation(int i, int j) {
    if (i > j)
        swap(i, j);
    if (j - i >= n / 2) {
        doSwap(i, j);
    } else if (j <= n / 2) {
        doSwap(i, n);
        doSwap(j, n);
        doSwap(i, n);
    } else if (i > n / 2) {
        doSwap(i, 1);
        doSwap(j, 1);
        doSwap(i, 1);
    } else {
        doSwap(1, j);
        doSwap(1, n);
        doSwap(i, n);
        doSwap(1, n);
        doSwap(1, j);
    }
}

int main() {

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    

    for (int i = 1; i <= n; ++i) {
        if (a[i] != i) {
            swap_operation(i, pos[i]);
        }
    }

    cout << ans.size() << endl;


    for (auto i: ans) {

        cout << i.first << ' ' << i.second << endl;
    }

    return 0;
}