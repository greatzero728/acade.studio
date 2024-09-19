#include <bits/stdc++.h>
using namespace std;

const int N = 200'005;
int n, q, a[N];
struct BIT {
    int bit[N];
    void upd(int x, int v) {
        for (int i = x; i < N; i |= i + 1) {
            bit[i] += v;
        }
    }
    int get(int r) {
        int ans = 0;
        for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
            ans += bit[i];
        }
        return ans;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
} t[3];
set<int> s[3];
void add(int i) {
    s[a[i]].insert(i);
    t[a[i]].upd(i, 1);
}
void rem(int i) {
    s[a[i]].erase(i);
    t[a[i]].upd(i, -1);
}
int first(int x) {
    return *s[x].begin();
}
int last(int x) {
    return *s[x].rbegin();
}
int win(int x) {
    return (x + 1) % 3;
}
int lose(int x) {
    return (x + 2) % 3;
}
int query() {
    if (s[0].empty() + s[1].empty() + s[2].empty() == 2) { //one shape
        return n;
    }
    if (s[0].empty() + s[1].empty() + s[2].empty() == 1) { //two shapes
        for (int x = 0; x < 3; x++) {
            if (s[x].empty()) {
                return s[(x + 1) % 3].size();
            }
        }
    }
    int ans = n;
    for (int x = 0; x < 3; x++) {
        int l = first(lose(x)), r = first(win(x));
        if (l < r) {
            ans -= t[x].get(l + 1, r - 1);
        }
        l = last(win(x)), r = last(lose(x));
        if (l < r) {
            ans -= t[x].get(l + 1, r - 1);
        }
    }
    return ans;
}
int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        a[i] = (c == 'R'? 0 : (c == 'S'? 1 : 2));
        add(i);
    }
    cout << query() << '\n';
    while (q--) {
        int p;
        char c;
        cin >> p >> c;
        p--;
        int x = (c == 'R'? 0 : (c == 'S'? 1 : 2));
        rem(p);
        a[p] = x;
        add(p);
        cout << query() << '\n';
    }
}