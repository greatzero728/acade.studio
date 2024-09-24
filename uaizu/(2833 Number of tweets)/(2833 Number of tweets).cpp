#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 10;

int n, k;
int to[MX], disEnd[MX];
vector<int> tweet[MX], rev[MX];

void calc() {
    queue<int> bfs;
    memset(disEnd, -1, sizeof(disEnd));
    for (int i = 0; i < n; i++) {
        if (tweet[i].empty()) {
            bfs.push(i);
            disEnd[i] = 0;
        }
    }
    while (!bfs.empty()) {
        int curr = bfs.front();
        bfs.pop();
        for (auto &x: rev[curr]) {
            if (disEnd[x] == -1) {
                disEnd[x] = disEnd[curr] + 1;
                bfs.push(x);
            }
        }
    }
}

int cntt() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (k > disEnd[i] || rev[i].empty()) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> to[i];
        if (to[i] > 0) {
            tweet[to[i] - 1].push_back(i);
            rev[i].push_back(to[i] - 1);
        }
    }
    calc();
    int res = cntt();
    cout << res << "\n";
    return 0;
}
