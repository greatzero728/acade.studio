#include "bits/stdc++.h"


#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rep1(i, n) for (int i = 1; i < (n); ++i)
#define rep1n(i, n) for (int i = 1; i <= (n); ++i)
#define repr(i, n) for (int i = (n) - 1; i >= 0; --i)
#define pb push_back
#define eb emplace_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define each(x, a) for (auto &x : a)
#define ar array
#define vec vector
#define range(i, n) rep(i, n)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using str = string;
using pi = pair<int, int>;
using pl = pair<ll, ll>;

using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pair<int, int>>;
using vvi = vector<vi>;

int Bit(int mask, int b) { return (mask >> b) & 1; }

template<class T>
bool ckmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool ckmax(T &a, const T &b) {
    if (b > a) {
        a = b;
        return true;
    }
    return false;
}

const int INFi = 2e9;
const ll INF = 2e18;
const int LG = 15;

vi get(string A, char x) {
    int cur = 0;
    vi res;
    for (int i = 0; i < A.size(); ++i) {
        if (i && A[i] != A[i - 1]) {
            res.push_back(cur);
            cur = 0;
        }
        cur++;
    }
    res.push_back(cur);
    if (A.back() == x) {
        res.pop_back();
    }
    return res;
}

vpi solve(string s, string t) {
    vpi ans;
    vi As = get(s, 'a'), Bs = get(t, 'b');
    int posA = accumulate(all(As), 0);
    int posB = accumulate(all(Bs), 0);
    auto Do = [&](int x, int y) {
        ans.emplace_back(x, y);
        if (ans.size() == 1) {
            string s2 = t.substr(0, y) + s.substr(x, s.size());
            string t2 = s.substr(0, x) + t.substr(y, t.size());
            swap(s, s2);
            swap(t, t2);
        }
    };
    if (As.size() > Bs.size() + 1 && !Bs.empty()) {
        int i = 0;
        if (As.size() % 2 == 0) i++;
        while (i + 2 < As.size()) {
            int nxtL = (i + 2) - 1 + (int) Bs.size();
            int nxtR = (int) As.size() - (i + 3);
            if (Bs.size() % 2 == 0) {
                nxtL--;
                nxtR++;
            }
            if (nxtL - nxtR >= 2) break;
            i += 2;
        }
        int valA = 0, valB = Bs[0];
        rep(j, i + 1) valA += As[j];
        if (Bs.size() % 2 == 0) valB += Bs[1];
        Do(valA, valB);
    } else if (Bs.size() > As.size() + 1 && !As.empty()) {
        int i = 0;
        if (Bs.size() % 2 == 0) i++;
        while (i + 2 < Bs.size()) {
            int nxtL = i + 1 + (int) As.size();
            int nxtR = (int) Bs.size() - (i + 3);
            if (As.size() % 2 == 0) {
                nxtL--;
                nxtR++;
            }
            if (nxtL - nxtR >= 2) break;
            i += 2;
        }
        int valA = As[0], valB = 0;
        rep(j, i + 1) valB += Bs[j];
        if (As.size() % 2 == 0) valA += As[1];
        Do(valA, valB);
    }

    As = get(s, 'a'), Bs = get(t, 'b');
    posA = accumulate(all(As), 0);
    posB = accumulate(all(Bs), 0);
    while (posA != 0 || posB != 0) {
        if ((posA != 0 && posB != 0) || (As.size() <= 3 && Bs.size() <= 3)) {
            Do(posA, posB);
            if (!As.empty()) {
                posA -= As.back();
                As.pop_back();
            }
            if (!Bs.empty()) {
                posB -= Bs.back();
                Bs.pop_back();
            }
            swap(As, Bs);
            swap(posA, posB);
            continue;
        }
        if (posA == 0) {
            int t = (int) Bs.size() / 2;
            if (t % 2) t--;
            rep(_, t) {
                As.push_back(Bs.back());
                Bs.pop_back();
            }
            reverse(all(As));
            swap(As, Bs);
            for (auto &x: As) {
                posA += x;
                posB -= x;
            }
            Do(0, posA);
            posA -= As.back();
            As.pop_back();
        } else {
            int t = (int) As.size() / 2;
            if (t % 2) t--;
            rep(_, t) {
                Bs.push_back(As.back());
                As.pop_back();
            }
            reverse(all(Bs));
            swap(As, Bs);
            for (auto &x: Bs) {
                posB += x;
                posA -= x;
            }
            Do(posB, 0);
            posB -= Bs.back();
            Bs.pop_back();
        }
    }
//    cout << s << ' ' << t << '\n';
    return ans;
}

void solve() {
    string s, t;
    cin >> s >> t;
    auto ans1 = solve(s, t);
    auto ans2 = solve(t, s);
    if (ans1.size() < ans2.size()) {
        cout << ans1.size() << '\n';
        for (auto &[x, y]: ans1) cout << x << ' ' << y << '\n';
    } else {
        cout << ans2.size() << '\n';
        for (auto &[y, x]: ans2) cout << x << ' ' << y << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(15) << fixed;
    int t = 1;
//    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve();
    }
    return 0;
}
