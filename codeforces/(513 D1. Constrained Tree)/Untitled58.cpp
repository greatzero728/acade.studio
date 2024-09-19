#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#define SZ(x) ((int)(x).size())
#define FOR(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
using namespace std;
typedef long long LL;

const int N = 1000005;
vector<int> l[N], r[N];
int minL[N], minR[N], maxL[N], maxR[N];
int tree[N][2];
int flag = 0;
vector<int> ans;
int st[N], top;

int p[N], q[N];
int g[N];

int FIND(int x) { return g[x]==x? x: (g[x]=FIND(g[x])); }
void UNION(int x, int y) {
  if(FIND(x) == FIND(y)) return;
  x = FIND(x); y = FIND(y);
  p[x] = min(p[x], p[y]);
  q[x] = max(q[x], q[y]);
  g[y] = x;
}

void go(int L, int R) {
  int x = L;
  //printf("x=%d, %d, %d, %d, %d (L=%d, R=%d)\n", x, minL[x], maxL[x], minR[x], maxR[x], L, R);
  if (minL[x] && minL[x] <= L) { flag = 1; return; }
  if (maxL[x] && maxL[x] > R) { flag = 1; return; }
  if (minR[x] && minR[x] <= L) { flag = 1; return; }
  if (maxR[x] && maxR[x] > R) { flag = 1; return; }
  if (maxL[x] && minR[x] && maxL[x] >= minR[x]) { flag = 1; return; }
  if (minR[x]) {
    if (minR[x] > L+1) go(L+1, minR[x]-1);
    ans.push_back(x);
    go(minR[x], R);
  } else if (maxL[x]) {
    go(L+1, maxL[x]);
    ans.push_back(x);
    if (maxL[x] < R) go(maxL[x]+1, R);
  } else {
    if (L+1 <= R) go(L+1, R);
    ans.push_back(x);
  }
}

int main(void) {
  int n, m; 
  scanf("%d%d", &n, &m);
  for(int i=0;i<m;i++) {
    char s[10];
    int x, y;
    scanf("%d%d%s", &x, &y, s);
    if (x > y) { flag = 1; }
    if (s[0] == 'L') {
      l[x].push_back(y);
    } else {
      r[x].push_back(y);
    }
  }
  for(int i=1;i<=n;i++) g[i] = p[i] = q[i] = i;
  for(int x=n;x>=1;x--) {
    int ll = 0, rr = 0;
    if (SZ(l[x])) ll = l[x][0];
    if (SZ(r[x])) rr = r[x][0];
    FOR(it, l[x]) {
      int y = *it;
      UNION(ll, y);
    }
    while(ll && top && st[top-1] <= q[FIND(ll)]) {
      UNION(ll, st[top-1]);
      --top;
    }

    FOR(it, r[x]) {
      int y = *it;
      UNION(rr, y);
    }
    while(rr && top && st[top-1] <= q[FIND(rr)]) {
      UNION(rr, st[top-1]);
      --top;
    }
    ll = FIND(ll);
    rr = FIND(rr);
    if(ll && rr && q[ll] >= p[rr]) flag = 1;
    minL[x] = p[ll];
    maxL[x] = q[ll];
    minR[x] = p[rr];
    maxR[x] = q[rr];
    if(ll) UNION(x, ll);
    if(rr) UNION(x, rr);


    st[top++] = x;
  }
  go(1, n);
  if(flag) puts("IMPOSSIBLE");
  else {
    FOR(it, ans) printf("%d ", *it);
    puts("");
  }
  return 0;
}
