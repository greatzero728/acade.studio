#include <bits/stdc++.h>

using namespace std;

#define all(a) a.begin(), a.end()

template<typename t>
class segTree {
public:
    vector<t> tree;
    int n;

    segTree(vector<vector<int>> &a) {
        n = a.size();
        if (__builtin_popcount(n) != 1)
            n = 1 << (__lg(n) + 1);
        this->tree.resize(n << 1, 1e9);
        for (int i = 0; i < a.size(); ++i) {
            if (!a[i].empty())
                tree[i + n] = a[i].front();
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[(i << 1) + 1]);
        }
    }

    t merge(t left, t right) {
        return max(left, right);
    }

    t query(int l, int r, int sl, int sr, int k) {
        if (r < sl || l > sr)
            return 0;
        if (l <= sl && r >= sr)
            return tree[k];
        int newSl = ((sl + sr) >> 1) + 1, newSr = (sl + sr) >> 1;
        t leftV = query(l, r, sl, newSr, k << 1), rightV = query(l, r, newSl, sr, (k << 1) + 1);
        return merge(leftV, rightV);
    }

    void update(int l, int r, t val, int k, int idx) {
        if (idx < l || idx > r)
            return;
        if (r == idx && l == idx) {
            tree[k] = val;
            return;
        }
        int newSl = ((l + r) >> 1) + 1, newSr = (l + r) >> 1;
        update(l, newSr, val, k << 1, idx);
        update(newSl, r, val, (k << 1) + 1, idx);
        tree[k] = merge(tree[k << 1], tree[(k << 1) + 1]);
    }

    t query(int l, int r) {
        return query(l, r, 0, n - 1, 1);
    }

    void update(int idx, t val) {
        update(0, n - 1, val, 1, idx);
    }
};

//x1, y1, x2, y2, idx
bool cmp1(vector<int> a, vector<int> b) {
    if (a[1] < b[1])
        return true;
    return false;
}


int main(){
    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);
    vector<vector<int>> rows(n + 1), columns(m + 1);
    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        rows[x].push_back(y);
        columns[y].push_back(x);
    }
    for (int i = 0; i <= n; ++i) {
        sort(all(rows[i]));
    }
    for (int i = 0; i <= m; ++i) {
        sort(all(columns[i]));
    }
    //x1, y1, x2, y2, idx
    vector<vector<int>> queries(q, vector<int>(5));
    vector<bool> res(q, false);
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < 4; ++j) {
            scanf("%d", &queries[i][j]);
        }
        queries[i][4] = i;
    }
    sort(all(queries), cmp1);
    segTree<int> seg(rows);
    int last = 0;
    vector<int> lastidx(n + 1, 0);
    for (int i = 0; i < q; ++i) {
        for (int j = last; j < queries[i][1]; ++j) {
            for (auto x: columns[j]) {
                bool upd = false;
                while (lastidx[x] < rows[x].size() && rows[x][lastidx[x]] < queries[i][1]) {
                    lastidx[x]++;
                    upd = true;
                }
                if (upd) {
                    if (lastidx[x] < rows[x].size())
                        seg.update(x, rows[x][lastidx[x]]);
                    else
                        seg.update(x, 1e9);
                }
            }
        }
        int cur = seg.query(queries[i][0], queries[i][2]);
        if (cur <= queries[i][3]) {
            res[queries[i][4]] = true;
        }
        last = queries[i][1];
    }
    sort(all(queries));
    seg = segTree<int> (columns);
    last = 0;
    lastidx = vector<int>(m + 1, 0);
    //x1, y1, x2, y2, idx
    for (int i = 0; i < q; ++i) {
        for (int j = last; j < queries[i][0]; ++j) {
            for (auto y: rows[j]) {
                bool upd = false;
                while (lastidx[y] < columns[y].size() && columns[y][lastidx[y]] < queries[i][0]) {
                    lastidx[y]++;
                    upd = true;
                }
                if (upd) {
                    if (lastidx[y] < columns[y].size())
                        seg.update(y, columns[y][lastidx[y]]);
                    else
                        seg.update(y, 1e9);
                }
            }
        }
        int cur = seg.query(queries[i][1], queries[i][3]);
        if (cur <= queries[i][2]) {
            res[queries[i][4]] = true;
        }
        last = queries[i][0];
    }
    for (int i = 0; i < q; ++i) {
        puts((res[i] ? "YES" : "NO"));
    }
}