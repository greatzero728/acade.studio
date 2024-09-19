#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cstring>
#include <numeric>
using namespace std;
typedef long long ll;
#define F0(i,n) for (int i = 0; i < n; i++)
#define F1(i,n) for (int i = 1; i <= n; i++)
#define CL(a,x) memset(x, a, sizeof(x));
#define SZ(x) ((int)x.size())
const double eps = 1e-10;
const int inf = 1000000009;
int i, j, k, m, n, l;
const int N = 1000005;
int a[N], b[N], maxc[N], maxl[N], minr[N];
string s[N];
vector<int> pr[N], fr[N];
vector<int> ans;

set<int> lefts;

void nope() {
    cout << "IMPOSSIBLE" << endl;
    exit(0);
}

int build(int i, int r) {
    r = max(r, maxc[i]);

    if (i == r) {
        ans.push_back(i);
        return i;
    }

    if (maxl[i] == 0) {
        ans.push_back(i);
        return build(i + 1, r);
    }

    int x = build(i + 1, maxl[i]);
    ans.push_back(i);

    F0(jj, SZ(fr[i])) {
        int k = fr[i][jj];
        if (s[k] == "RIGHT" && b[k] <= x) nope();
    }

    if (minr[i] < x) nope();
    if (x >= r) return x;

    return build(x + 1, r);
}

int main() {
    //freopen("x.in", "r", stdin);

    cin >> n >> m;
    F1(i, n) minr[i] = inf;
    F0(i, m) {
        cin >> a[i] >> b[i] >> s[i];
        if (a[i] >= b[i]) nope();
        if (s[i] == "LEFT") {
            maxl[a[i]] = max(maxl[a[i]], b[i]);
        }
        else {
            minr[a[i]] = min(minr[a[i]], b[i]);
        }
        pr[b[i]].push_back(i);
        fr[a[i]].push_back(i);
    }

    for (int i = n; i >= 1; i--) {
        maxc[i] = max(maxc[i], i);
        F0(jj, SZ(pr[i])) {
            int k = pr[i][jj];
            maxc[a[k]] = max(maxc[a[k]], maxc[i]);
        }
    }

    build(1, n);

    F0(i, n) cout << ans[i] << " ";
    
    return 0;
}
