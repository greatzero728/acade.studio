#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <cassert>

using namespace std;

#define LEFT 0
#define RIGHT 1

const int N = 1234567;

int a[N], b[N], dir[N];
int k;
vector <int> ret;

void solve(int root, int to) {
  if (root > to) {
    return;
  }
  if (root == to) {
    ret.push_back(root);
    return;
  }
  for (int split = root; split <= to; split++) {
    bool ok = true;
    for (int i = 0; i < k; i++) {
      if (root < a[i] && b[i] <= to) {
        if (a[i] <= split && split < b[i]) {
          ok = false;
          break;
        }
      }
      if (root == a[i]) {
        if (dir[i] == LEFT && split < b[i]) {
          ok = false;
          break;
        }
        if (dir[i] == RIGHT && split >= b[i]) {
          ok = false;
          break;
        }
      }
    }
    if (ok) {
      solve(root + 1, split);
      ret.push_back(root);
      solve(split + 1, to);
      return;
    }
  }
  puts("IMPOSSIBLE");
  exit(0);
}

int main() {
  int n;
  scanf("%d %d", &n, &k);
  char foo[42];
  for (int i = 0; i < k; i++) {
    scanf("%d %d %s", a + i, b + i, foo);
    if (a[i] < 1 || a[i] > n || b[i] < 1 || b[i] > n || b[i] <= a[i]) {
      puts("IMPOSSIBLE");
      return 0;
    }
    dir[i] = (foo[0] == 'L' ? LEFT : RIGHT);
  }
  ret.clear();
  solve(1, n);
  for (int i = 0; i < n - 1; i++) {
    printf("%d ", ret[i]);
  }
  printf("%d\n", ret[n - 1]);
  return 0;
}
