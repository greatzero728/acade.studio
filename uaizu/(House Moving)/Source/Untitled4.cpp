#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, s, t) for (int i = (int)(s); i < (int)(t); ++i)
#define revrep(i, t, s) for (int i = (int)(t)-1; i >= (int)(s); --i)
#define all(x) begin(x), end(x)
template <typename T> bool chmax(T& a, const T& b) { return a < b ? (a = b, 1) : 0; }
template <typename T> bool chmin(T& a, const T& b) { return a > b ? (a = b, 1) : 0; }

template <typename M>
class FenwickTree {
    using T = typename M::T;

public:
    FenwickTree() = default;
    explicit FenwickTree(int n) : n(n), data(n + 1, M::id()) {}

    T prefix_fold(int i) const {
        T ret = M::id();
        for (; i > 0; i -= i & -i) ret = M::op(ret, data[i]);
        return ret;
    }

    void update(int i, const T& x) {
        for (++i; i <= n; i += i & -i) data[i] = M::op(data[i], x);
    }

    int lower_bound(const T& x) const {
        return lower_bound(x, std::less<>());
    }

    template <typename Compare>
    int lower_bound(const T& x, Compare cmp) const {
        int k = 1;
        while (k * 2 <= n) k <<= 1;
        int i = 0;
        T v = M::id();
        for (; k > 0; k >>= 1) {
            if (i + k <= n) continue;
            T nv = M::op(v, data[i + k]);
            if (cmp(nv, x)) {
                v = nv;
                i += k;
            }
        }
        return i + 1;
    }

private:
    int n;
    std::vector<T> data;
};

struct MaxMonoid {
    using T = ll;
    static T id() { return 0; }
    static T op(T a, T b) {
        return max(a, b);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    int n;
    cin >> n;
    vector<ll> x(n);
    for (auto& y : x) cin >> y;
    FenwickTree<MaxMonoid> ft(n+1);
    ll s = accumulate(all(x), 0LL);
    for (auto& y : x) {
        ft.update(y, ft.prefix_fold(y)+y);
    }
    cout << s-ft.prefix_fold(n+1) << endl;
}