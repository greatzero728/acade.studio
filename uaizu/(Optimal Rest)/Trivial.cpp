#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>

using namespace std;

#define FOR(i,k,n) for(int i=(k); i<(int)(n); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORIT(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

template<class T> void debug(T begin, T end){ for(T i = begin; i != end; ++i) cerr<<*i<<" "; cerr<<endl; }
inline bool valid(int x, int y, int W, int H){ return (x >= 0 && y >= 0 && x < W && y < H); }

typedef long long ll;
const int INF = 100000000;
const double EPS = 1e-8;
const int MOD = 1000000007;
int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
const int MAX_N = 5000000;
typedef pair<int, int> P;
int trans(int n){
  return 64 / n;
}
int trans(string s){
  int base = 0;
  REP(i, s.size()) if(isdigit(s[i])) base = base * 10 + s[i] - '0';
  int all = trans(base);
  int cur = all;
  REP(i, s.size()) if(s[i] == '.'){
    cur /= 2;
    all += cur;
  }
  return all;
}

int main(){
  int T;
  cin >> T;
  static int dp[MAX_N];
  int val[7] = {64, 32, 16, 8, 4, 2, 1};
  int len[7] = {2, 2, 2, 2, 3, 3, 3};
  string expr[7] = {"R1", "R2", "R4", "R8", "R16", "R32", "R64"};
  vector<P> tool;
  vector<string> tool_expr;
  REP(i, 7){
    int sum = 0;
    int length = 0;
    string expression = "";
    for(int j = i; j < 7; j++){
      expression += (j == i) ? expr[i] : ".";
      sum += val[j];
      length += (j == i) ? len[j] : 1;
      tool.push_back(make_pair(sum, length));
      tool_expr.push_back(expression);
    }
  }
  REP(i, MAX_N) dp[i] = INF;
  dp[0] = 0;
  REP(i, MAX_N){
    REP(j, tool.size()){
      int s = tool[j].first, l = tool[j].second;
      if(i + s < MAX_N) dp[i + s] = min(dp[i + s], dp[i] + l);
    }
  }
  while(T--){
    string s; cin >> s;
    REP(i, s.size()) if(s[i] == 'R') s[i] = ' ';
    stringstream ss(s);
    int seq = 0;
    int all = 0;
    while(ss >> s){
      all += trans(s);
    }
    int cur = all;
    string ans;
    while(cur > 0){
      string next = "ZZZZZZZZZ";
      int next_c = cur;
      REP(i, tool.size()){
        int s = tool[i].first, l = tool[i].second;
        if(cur - s >= 0 && dp[cur - s] + l == dp[cur] && next + "RRRRRRRRR" > tool_expr[i] + "RRRRRRRR"){
          next = tool_expr[i];
          next_c = cur - s;
        }
      }
      ans += next;
      cur = next_c;
    }
    cout << ans << endl;
  }
  return 0;
}