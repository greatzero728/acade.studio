//#pragma comment(linker,"/STACK:100000000000,100000000000")

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#include <set>
#include <iomanip>
#include <queue>
#include <map>
#include <functional>
#include <list>
#include <sstream>
#include <ctime>
#include <climits>
#include <bitset>
#include <list>
#include <cassert>
#include <complex>

using namespace std;

/* Constants begin */
const long long inf = 2e18 + 7;
const long long mod = 1e9 + 7;
const double eps = 1e-9;
const double PI = 2*acos(0.0);
const double E = 2.71828;
/* Constants end */

/* Defines begin */
#define pb push_back
#define mp make_pair
#define ll long long
#define double long double
#define F first
#define S second
#define all(a) (a).begin(),(a).end()
#define forn(i, n) for (int (i)=0; (i)<(n); ++(i))
#define random (rand()<<16|rand())
#define sqr(x) (x)*(x)
#define base complex<double>
/* Defines end */

int n, m;
int num = 1;

int mxL[100005], mnR[100005], mxR[100005];

int g[100005][2];
bool bad = false;

bool dfs(int v, int mx) {
    mx = max(mx, mxR[v]);
    bool ok = true;
    if (mxL[v]) {
        g[v][0] = num;
        ok &= dfs(num++, mxL[v]);
    }
    if (num - 1 >= mnR[v]) {
        ok = false;
    }
    if (num - 1 < mx) {
        g[v][1] = num;
        ok &= dfs(num++, mx);
    }
    return ok;
}

void out(int v) {
    if (!v) {
        return;
    }
    out(g[v][0]);
    printf("%d ", v);
    out(g[v][1]);
}

int main(void) {
    #ifdef nobik
        freopen("input.txt", "rt", stdin);
        freopen("output.txt", "wt", stdout);
    #endif
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        mnR[i] = mod;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        char c[15];
        scanf("%d %d %s", &a, &b, c);
        if (a >= b) {
            bad = true;
        }
        if (c[0] == 'L') {
            mxL[a] = max(mxL[a], b);
        } else {
            mnR[a] = min(mnR[a], b);
            mxR[a] = max(mxR[a], b);
        }
    }
    bad |= dfs(num++, n) ^ 1;
    if (bad) {
        printf("IMPOSSIBLE\n");
        exit(0);
    }
    out(1);
    printf("\n");
    return 0;
}
