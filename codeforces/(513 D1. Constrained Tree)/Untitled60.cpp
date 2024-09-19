#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int MAXN = 1000000 + 10;
const char *FAIL = "IMPOSSIBLE";

int min_l[MAXN], max_r[MAXN], last[MAXN];
std::vector <int> ans;
int n, c;
namespace seg_tree {
  int max[MAXN << 2];
  void _modify(int node, int l, int r, int p, int v) {
    if (l == r) {
      max[node] = std::max(max[node], v);
      return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) _modify(node << 1, l, mid, p, v);
    else _modify(node << 1 | 1, mid + 1, r, p, v);
    max[node] = std::max(max[node << 1],
                         max[node << 1 | 1]);
  }
  void modify(int p, int v) {
    _modify(1, 1, n, p, v);
  }
  int _query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return max[node];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) ans = std::max(ans, _query(node << 1, l, mid, ql, qr));
    if (qr > mid) ans = std::max(ans, _query(node << 1 | 1, mid + 1, r, ql, qr));
    return ans;
  }
  int query(int l, int r) {
    return _query(1, 1, n, l, r);
  }
}
void solve(int l, int r) {
  if (l > r) return;
  if (last[l] > r) throw 233;
  if (l == r) {
    ans.push_back(l);
    return;
  }
  if (max_r[l] == l) {
    ans.push_back(l);
    solve(l + 1, r);
    return;
  }

  int nxtv = seg_tree::query(l + 1, max_r[l]);
  if (nxtv >= min_l[l]) throw 666;
  else if (nxtv >= max_r[l]) {
    solve(l + 1, nxtv);
    ans.push_back(l);
    solve(nxtv + 1, r);
  } else {
    throw -1;
  }

}
int main() {

  scanf("%d%d", &n, &c);

  for (int i = 1; i <= n; i++) {
    min_l[i] = n + 1;
    max_r[i] = i;
    last[i] = i;
  }
  
  for (int i = 1; i <= c; i++) {
    int a, b;
    char buff[10];
    scanf("%d%d%s", &a, &b, buff);
    if (a >= b) {
      puts(FAIL);
      return 0;
    }

    if (buff[0] == 'L') {
      max_r[a] = std::max(max_r[a], b);
      last[a] = std::max(last[a], b);
    } else {
      min_l[a] = std::min(min_l[a], b);
      last[a] = std::max(last[a], b);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (min_l[i] <= max_r[i]) {
      fprintf(stderr, "A");
      puts(FAIL);
      return 0;
    }
  }

  seg_tree::modify(n, last[n]);
  for (int i = n - 1; i >= 1; i--) {
    last[i] = std::max(last[i], seg_tree::query(i, last[i]));
    seg_tree::modify(i, last[i]);
  }

  try {
    solve(1, n);
  } catch (int x) {
    if (x > 0) {
      fprintf(stderr, "B%d", x);
      puts(FAIL);
    } else {
      throw;
    }
    return 0;
  }

  for (auto i: ans) {
    printf("%d ", i);
  }

  printf("\n");
  
}
