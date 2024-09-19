#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int N = 1e6;

vector<int> sub[N + 1];
vector<int> ans;
int i;

void fail() { cout << "IMPOSSIBLE\n", exit(0); }

void inord(int mi, int ma) {
  if (i > ma) fail();
  if (i >= mi) return;
  int v = ++i, maxl = v, minr = ma + 1, maxr = mi;
  for (int x: sub[v]) {
    if (x & 1) {
      minr = min(minr, x / 2);
      maxr = max(maxr, x / 2);
    } else {
      maxl = max(maxl, x / 2);
    }
  }
  inord(maxl, minr - 1);
  ans.push_back(v);
  inord(maxr, ma);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, c; cin >> n >> c;
  while (c--) {
    int a, b; string s; cin >> a >> b >> s;
    sub[a].push_back(b * 2 + (s[0] == 'R'));
    if (a >= b) fail();
  }
  inord(n, n);
  for (auto x: ans) cout << x << ' ';
}