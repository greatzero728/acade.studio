#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;
const int maxm = 4 * maxn;
const int inf = 1e18;

int n, m, q;
int a[11][maxn];

struct node {
    int f[21];
    int l, r, cnt;
};

int fa[41], rem[41];
node pre[maxn];

int find(int i) {
    return fa[i] == i ? fa[i] : fa[i] = find(fa[i]);
}

node merge(node x, node y) {
    node z;
    z.l = x.l, z.r = y.r, z.cnt = x.cnt + y.cnt;

    for (int i = 1; i <= 4 * n; i++) {
        fa[i] = i, rem[i] = 0;
    }

    for (int i = 1; i <= 2 * n; i++) {
        y.f[i] += 2 * n;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i][x.r] == a[i][y.l]) {
            int X = find(x.f[i + n]), Y = find(y.f[i]);
            if (X != Y) {
                fa[X] = Y, z.cnt--;
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int P;
        P = find(x.f[i]);
        if (!rem[P]) {
            rem[P] = ++cnt;
        }
        z.f[i] = rem[P];

        P = find(y.f[i + n]);
        if (!rem[P]) {
            rem[P] = ++cnt;
        }
        z.f[i + n] = rem[P];
    }

    return z;
}

struct sgt {
    node f[maxm];

    void build(int i, int l, int r) {
        if (l == r) {
            f[i] = pre[l];
            return;
        }
        build(i * 2, l, (l + r) / 2);
        build(i * 2 + 1, (l + r) / 2 + 1, r);
        f[i] = merge(f[i * 2], f[i * 2 + 1]);
    }

    node qry(int i, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return f[i];
        }
        if (qr <= (l + r) / 2) {
            return qry(i * 2, l, (l + r) / 2, ql, qr);
        }
        if (ql > (l + r) / 2) {
            return qry(i * 2 + 1, (l + r) / 2 + 1, r, ql, qr);
        }
        return merge(qry(i * 2, l, (l + r) / 2, ql, qr), qry(i * 2 + 1, (l + r) / 2 + 1, r, ql, qr));
    }
} tree;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    for (int j = 1; j <= m; j++) {
        pre[j].l = pre[j].r = j;
        for (int i = 1; i <= n; i++) {
            pre[j].f[i] = pre[j].f[i + n] = (a[i][j] == a[i - 1][j]) ? pre[j].f[i - 1] : pre[j].f[i - 1] + 1;
        }
        pre[j].cnt = pre[j].f[n];
    }

    tree.build(1, 1, m);

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << tree.qry(1, 1, m, l, r).cnt << "\n";
    }

    return 0;
}