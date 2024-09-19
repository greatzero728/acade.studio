#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

const int MAXN = 110;
const int inf = 1e9;

struct Edge {
  int b;
  bool isleft;
};

vector<Edge> E[MAXN];
char s[11];

int can[MAXN][MAXN];
int lo[MAXN], hi[MAXN];
int lefth[MAXN], rightl[MAXN];

void impossible() {
  puts("IMPOSSIBLE");
  exit(0);
}

int solve(int l, int h) {
  if (l > h) return 1;
  if (can[l][h] != -1) return can[l][h];
  
  for (int i = l; i <= h; ++i)
    if (!(l <= lo[i] && hi[i] <= h)) return can[l][h] = 0;

  for (int i = l; i <= h; ++i)
    if (i >= lefth[l] && i+1 <= rightl[l])
      if (solve(l+1, i) && solve(i+1, h)) return can[l][h] = 1;

  return can[l][h] = 0;
}

vector<int> ans;

void rec(int l, int h) {
  if (l > h) return;
  assert(can[l][h]);

  for (int i = l; i <= h; ++i)
    if (i >= lefth[l] && i+1 <= rightl[l])
      if (solve(l+1, i) && solve(i+1, h)) {
        rec(l+1, i);
        ans.push_back(l);
        rec(i+1, h);
        return;
      }
  assert(false);
}

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);
  REP(i, m) {
    int a, b;
    scanf("%d %d %s", &a, &b, s);
    --a, --b;
    E[a].push_back({b, s[0] == 'L'});
    if (a >= b) impossible();
  }

  for (int i = n-1; i >= 0; --i) {
    lo[i] = hi[i] = i;
    int leftlo = inf, lefthi = -inf;
    int rightlo = inf, righthi = -inf;
    for (Edge &e: E[i])
      if (e.isleft) {
        leftlo = min(leftlo, lo[e.b]);
        lefthi = max(lefthi, hi[e.b]);
      } else {
        rightlo = min(rightlo, lo[e.b]);
        righthi = max(righthi, hi[e.b]);
      }

    if (lefthi >= rightlo)
      impossible();

    lo[i] = min({lo[i], leftlo, rightlo});
    hi[i] = max({hi[i], lefthi, righthi});

    lefth[i] = lefthi;
    rightl[i] = rightlo;
  }
  
  memset(can, -1, sizeof(can));
  if (!solve(0, n-1)) impossible();

  rec(0, n-1);
  assert((int)ans.size() == n);
  REP(i, n)
    printf("%d%c", ans[i]+1, " \n"[i+1 == n]);

  return 0;
}
