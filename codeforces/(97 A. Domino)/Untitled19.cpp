#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
const int inf = 1000000005;
typedef long long ll;
using namespace std;
const double eps = 1e-9;
int m, i, j, k, n, ans, first;
string s[100], p[100];
int c[14][4], col[14];
int v[28][2], vn[28], used[7][7], done[28];

int get(char c) {
   if (c >= 'a' && c <= 'z') return c - 'a';
   return c - 'A' + 26;
}

void recolor() {
 k = 0;
 for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         if (s[i][j] != '.' && !isdigit(s[i][j])) {
            s[i][j] = col[k]+'0';
            s[i][j+1] = col[k]+'0';
            s[i+1][j] = col[k]+'0';
            s[i+1][j+1] = col[k]+'0';
            ++k;           
         }
     
}

void out() {
   for (i = 0; i < m; i++) {
      cout << s[i] << endl;
   }
}

void go(int at, int canUse) {
   if (canUse > 6) canUse = 6;
   if (at == 14) {
      ans++;
     // cout << ans << endl;
      
      if (!first) {
         recolor();
         first = 1;
      }
      //out();   
      //exit(0);
      return;
   }
   int i, j, x, y;
   for (col[at] = 0; col[at] <= canUse; col[at]++) {
      for (i = 0; i < 4; i++) {
         j = c[at][i];
         v[j][ vn[j]++ ] = col[at];
      }
      int sg = 1;
      for (i = 0; i < 4; i++) {
         j = c[at][i];
         if (vn[j] == 2 && done[j] == 0) {
            done[j] = at + 1;
            x = v[j][0];
            y = v[j][1];
            if (x > y) swap(x, y);
            used[x][y]++;
            if (used[x][y] > 1) sg = 0;
         }
      }
      if (sg) go(at + 1, max(canUse, col[at] + 1));
      for (i = 0; i < 4; i++) {
         j = c[at][i];
         if (vn[j] == 2 && done[j] == at + 1) {
            done[j] = 0;
            x = v[j][0];
            y = v[j][1];
            if (x > y) swap(x, y);
            used[x][y]--;
         }
      }
      
      for (i = 0; i < 4; i++) {
         j = c[at][i];
         vn[j]--;
      }
   }
}

int main() {
   cin >> m >> n;
   for (i = 0; i < m; i++) cin >> s[i];   
   for (i = 0; i < m; i++) {  
      p[i] = s[i];
   }
   for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         if (p[i][j] != '.') {
            c[k][0] = get(p[i][j]);
            c[k][1] = get(p[i][j+1]);
            c[k][2] = get(p[i+1][j]);
            c[k][3] = get(p[i+1][j+1]);
            k++;
            p[i][j] = p[i+1][j+1] = p[i][j+1] = p[i+1][j] = '.';
         }
   go(0, 0);
   cout << ans * 5040 << endl;
   out();
   return 0;
}