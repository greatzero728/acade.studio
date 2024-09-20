#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> ii;

const int Maxb = 64;
const int Maxn = 505;
const int Maxk = 8;
const int Maxn2 = 2 * Maxn;
const int Maxq = 600006;
const int Maxl = 4 * Maxq;

char tmp[100];
int tpnt;
int n, m;
char B[Maxn][Maxn];
vector <ii> bydiag[Maxn2];
int root;
int L[Maxn2], R[Maxn2];
vector <int> quer[Maxn2];
ull dp[Maxn][Maxn][Maxk];
int q;
bool res[Maxq];
int X1[Maxq], Y1[Maxq], X2[Maxq], Y2[Maxq];
char resstr[Maxl];
int rpnt;

int readInt()
{
    while (!isdigit(tmp[tpnt]))
        tpnt++;
    int res = 0;
    while (isdigit(tmp[tpnt]))
        res = 10 * res + (tmp[tpnt++] - '0');
    return res;
}

void readOne(int &a)
{
    gets(tmp);
    tpnt = 0;
    a = readInt();
}

void readTwo(int &a, int &b)
{
    gets(tmp);
    tpnt = 0;
    a = readInt();
    b = readInt();
}

void readFour(int &a, int &b, int &c, int &d)
{
    gets(tmp);
    tpnt = 0;
    a = readInt();
    b = readInt();
    c = readInt();
    d = readInt();
}

int getDiag(int l, int r)
{
    if (l > r) return 0;
    int lst = l + r >> 1;
    L[lst] = getDiag(l, lst - 1);
    R[lst] = getDiag(lst + 1, r);
    return lst;
}

void addQuery(int v, int lef, int rig, int qind)
{
    if (lef <= v && v <= rig) quer[v].push_back(qind);
    else if (rig < v) addQuery(L[v], lef, rig, qind);
    else addQuery(R[v], lef, rig, qind);
}

void Solve(int v, int lef, int rig)
{
    if (L[v]) Solve(L[v], lef, v - 1);
    if (R[v]) Solve(R[v], v + 1, rig);
    if (quer[v].empty()) return;
    int sz = (bydiag[v].size() - 1) / Maxb + 1;
    for (int i = 0; i < bydiag[v].size(); i++) {
        ii p = bydiag[v][i];
        fill(dp[p.first][p.second], dp[p.first][p.second] + sz, 0);
        if (B[p.first][p.second] != '#')
            dp[p.first][p.second][i / Maxb] |= ull(1) << ull(i % Maxb);
    }
    for (int i = v - 1; i >= lef; i--)
        for (int j = 0; j < bydiag[i].size(); j++) {
            ii p = bydiag[i][j];
            if (B[p.first][p.second] == '#')
                fill(dp[p.first][p.second], dp[p.first][p.second] + sz, 0);
            else if (p.first + 1 <= n && p.second + 1 <= m)
                for (int k = 0; k < sz; k++)
                    dp[p.first][p.second][k] = (dp[p.first + 1][p.second][k] | dp[p.first][p.second + 1][k]);
            else if (p.first + 1 <= n)
                for (int k = 0; k < sz; k++)
                    dp[p.first][p.second][k] = dp[p.first + 1][p.second][k];
            else for (int k = 0; k < sz; k++)
                    dp[p.first][p.second][k] = dp[p.first][p.second + 1][k];
        }
    for (int i = v + 1; i <= rig; i++)
        for (int j = 0; j < bydiag[i].size(); j++) {
            ii p = bydiag[i][j];
            if (B[p.first][p.second] == '#')
                fill(dp[p.first][p.second], dp[p.first][p.second] + sz, 0);
            else if (p.first - 1 > 0 && p.second - 1 > 0)
                for (int k = 0; k < sz; k++)
                    dp[p.first][p.second][k] = (dp[p.first - 1][p.second][k] | dp[p.first][p.second - 1][k]);
            else if (p.first - 1 > 0)
                for (int k = 0; k < sz; k++)
                    dp[p.first][p.second][k] = dp[p.first - 1][p.second][k];
            else for (int k = 0; k < sz; k++)
                    dp[p.first][p.second][k] = dp[p.first][p.second - 1][k];
        }
    for (int i = 0; i < quer[v].size(); i++) {
        int ind = quer[v][i];
        for (int k = 0; k < sz && !res[ind]; k++)
            res[ind] = (dp[X1[ind]][Y1[ind]][k] & dp[X2[ind]][Y2[ind]][k]) != ull(0);
    }
}

int main()
{
    readTwo(n, m);
    for (int i = 1; i <= n; i++)
        gets(B[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            bydiag[i + j].push_back({i, j});
    root = getDiag(2, n + m);
    readOne(q);
    for (int i = 0; i < q; i++) {
        readFour(X1[i], Y1[i], X2[i], Y2[i]);
        addQuery(root, X1[i] + Y1[i], X2[i] + Y2[i], i);
    }
    Solve(root, 2, n + m);
    for (int i = 0; i < q; i++)
        if (res[i]) {
            resstr[rpnt++] = 'Y';
            resstr[rpnt++] = 'e';
            resstr[rpnt++] = 's';
            resstr[rpnt++] = '\n';
        } else {
            resstr[rpnt++] = 'N';
            resstr[rpnt++] = 'o';
            resstr[rpnt++] = '\n';
        }
    resstr[rpnt] = '\0';
    puts(resstr);
    return 0;
}
