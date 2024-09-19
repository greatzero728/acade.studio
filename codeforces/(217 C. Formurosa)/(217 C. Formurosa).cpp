#include <bits/stdc++.h>
using namespace std;

int n, i;
string s;

int performOperation(char op, int x, int y) {
 if(op == '&') return x & y;
 if(op == '|') return x | y;
 if(op == '^') return x ^ y;
 assert(false);
}

int evaluateExpression() {
 ++i;
 if(s[i] == '0') return 1;
 if(s[i] == '1') return 8;
 if(s[i] == '?') return 6;
 int left = evaluateExpression();
 char operation = s[++i];
 int right = evaluateExpression();
 int result = 0;
 for(int a = 0; a < 4; ++a) {
  for(int b = 0; b < 4; ++b) {
   if((left & (1ll << a)) && (right & (1ll << b))) {
    result |= (1ll << performOperation(operation, a, b));
   }
  }
 }
 ++i;
 return result;
}

signed main() {
 cin >> n >> s;
 s = " " + s;
 cout << ((evaluateExpression() & 6) ? "YES" : "NO") << endl;
}