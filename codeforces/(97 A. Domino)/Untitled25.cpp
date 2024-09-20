#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <stack>
#include <sstream>
#include <cstring>
#include <numeric>
#include <ctime>

#define re return
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define y0 y32479
#define y1 y95874
#define fill(x, y) memset(x, y, sizeof(x))
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef long long ll;
typedef double D;
typedef long double LD;


template<class T> T abs(T x) {return x > 0 ? x : -x;}

int n;
int m;

string s[30];
string ans[30];
string sans[30];
vii v[30];

int get(char c) {
    if (c <= 'B')
        re c - 'A';
    else
        re c - 'a' + 2;
}

char lol(int x) {
    if (x < 2)
        re x + 'A';
    else
        re (x - 2) + 'a';
}

int t;
int was[100];

int getH(int a, int b) {
    if (a > b)
        swap(a, b);
    re (a - 48) * 7 + b - 48;
}

int check() {
    t++;
    rep(i, 28) {
        int o = getH(ans[v[i][0].fi][v[i][0].se],
                ans[v[i][1].fi][v[i][1].se]);
        if (was[o] == t)
            re 0;
        was[o] = t;
    }

    rep(i, n)
    sans[i] = ans[i];
    re 1;
}

int col[15];
int xx[100], yy[100];
int o[100][100];

int go(int p, int c) {
    if (p == 14) {
        re check();
    }
    int x = xx[p];
    int y = yy[p];
    ll aans = 0;
    for (int cc = 0; cc <= c; cc++) {
        if (col[cc] < 2) {
            col[cc]++;
            ans[x][y] = ans[x + 1][y] =
                ans[x][y + 1] = ans[x + 1][y + 1] = char(cc + 48);
            aans += go(p + 1, min(max(cc + 1, c), 6));
            col[cc]--;
        }
    }
    re aans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif

    cin >> n >> m;
    rep(i, n) {
        cin >> s[i];
        ans[i] = s[i];
    }

    int pp = 0;
    rep(i, n) rep(j, m)
        if (s[i][j] != '.') {
            if (!o[i][j]) {
                xx[pp] = i;
                yy[pp] = j;
                o[i][j] = o[i + 1][j] =
                        o[i][j + 1] = o[i + 1][j + 1] = 1;
                pp++;
            }
            v[get(s[i][j])].pb(mp(i, j));
        }

    ll aans = go(0, 0);
    cout << aans * 5040 << endl;
    rep(i, n)
        cout << sans[i] << endl;

    re 0;
}
