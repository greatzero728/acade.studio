#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;

struct SparseTable {
    vector<vector<int>> jmp;

    SparseTable(const vector<int> &v) {
        jmp.resize(1, v);
        for (int pw = 1, k = 1; pw * 2 <= v.size(); pw *= 2, ++k) {
            jmp.emplace_back(v.size() - pw * 2 + 1);
            for (int j = 0; j < jmp[k].size(); ++j) {
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
        }
    }
    int query(int l, int r) {
        assert(l <= r);
        int dep = 31 - __builtin_clz(r - l + 1);
        return min(jmp[dep][l], jmp[dep][r - (1 << dep) + 1]);
    }
};

int spf[N];

void sieve() {
    std::iota(spf, spf + N, 0);
    spf[1] = 1;
    for (long long i = 2; i < N; i++) {
        if (spf[i] == i) {
            for (long long j = i * i; j < N; j += i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

int main() {
    sieve();
    int n, q;
    cin >> n >> q;
    vector<int> a(n);

    map<int, int> last_occ;
    vector<int> nxt(n + 1, n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        int tmp = a[i];
        while (tmp > 1) {
            int p = spf[tmp];
            if (last_occ.count(p)) {
                nxt[last_occ[p]] = min(nxt[last_occ[p]], i);
            }
            last_occ[p] = i;
            while (tmp % p == 0) tmp /= p;
        }
    }

    vector<vector<int>> anc(n + 1, vector<int>(__lg(n) + 1, n));
    SparseTable table(nxt);
    for (int i = 0; i < n; ++i) {
        anc[i][0] = table.query(i, nxt[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 1; j <= __lg(n); ++j) {
            anc[i][j] = anc[anc[i][j - 1]][j - 1];
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int cur = l;
        int ans = 0;
        for (int i = __lg(n); i >= 0; --i) {
            if (anc[cur][i] <= r) {
                ans += (1 << i);
                cur = anc[cur][i];
            }
        }
        cout << ans + 1 << endl;
    }
}