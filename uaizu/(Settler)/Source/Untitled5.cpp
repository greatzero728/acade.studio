#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) begin(v), end(v)
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, s, n) for(int i = (int)(s); i < (int)(n); i++)
#define min(...) min({__VA_ARGS__})
#define max(...) max({__VA_ARGS__})

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

using pint = pair<int, int>;
using tint = tuple<int, int, int>;
using vint = vector<int>;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

struct FordFulkerson {
  struct edge {
    int to, cap, rev;
    edge(){}
    edge(int to, int cap, int rev):to(to), cap(cap), rev(rev){}
  };
  vector< vector<edge> > graph;
  vector<bool> used;
  FordFulkerson(){}
  FordFulkerson(int V):graph(V), used(V){}
  pair<int, int> add_edge(int from, int to, int cap) {
    graph[from].emplace_back(to, cap, graph[to].size());
    graph[to].emplace_back(from, 0, graph[from].size()-1);
    return make_pair(graph[from].size()-1, graph[to].size()-1);
  }
  int dfs(int v, int t, int f, int k = inf) {
    if(v == t) return f;
    if(k == 0) return 0;
    used[v] = true;
    for(edge& e : graph[v]) {
      if(!used[e.to] && e.cap > 0) {
	int d = dfs(e.to, t, min(f, e.cap), k-1);
	if(d > 0) {
	  e.cap -= d;
	  graph[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  int max_flow(int s, int t, int ff = inf, int k = inf) {
    if(s == t) return 0;
    int flow = 0;
    while(ff) {
      fill(all(used), false);
      int f = dfs(s, t, inf, k);
      if(f == 0) return flow;
      flow += f;
      ff -= f;
    }
    return flow;
  }
};

#define MAX_N 6000

int N, K;
int x[MAX_N], y[MAX_N];

int sq(int x) {
  return x*x;
}

int dist(int i, int j) {
  return sq(x[i]-x[j]) + sq(y[i]-y[j]);
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  cin >> N >> K;
  rep(i, N) cin >> x[i] >> y[i];

  int s = N, t = s + 1, V = t + 1;
  FordFulkerson graph(V);
  vector<int> eid(N);
  rep(i, N) {
    if(y[i]%2 == 0) eid[i] = graph.add_edge(s, i, 1).first;
    else eid[i] = graph.add_edge(i, t, 1).first;
    reps(j, i+1, N) {
      if(y[i]%2 != y[j]%2 && dist(i, j) < 4) {
	if(y[i]%2 == 0) graph.add_edge(i, j, inf);
	else graph.add_edge(j, i, inf);
      }
    }
  }

  int mx_st = N - graph.max_flow(s, t);
  if(mx_st < K) {
    cout << -1 << endl;
    return 0;
  }

  vector<int> ans;
  rep(i, N) {
    if(ans.size() == K) break;
    auto& e = y[i]%2 ? graph.graph[i][eid[i]] : graph.graph[s][eid[i]];
    int cap = e.cap;
    int rcap = graph.graph[e.to][e.rev].cap;
    e.cap = inf;
    int f = graph.max_flow(s, t);
    if(mx_st - f >= K) {
      ans.push_back(i);
      mx_st -= f;
    } else {
      e.cap = cap;
      graph.graph[e.to][e.rev].cap = rcap;
      if(y[i]%2 == 0) graph.max_flow(t, i, f, 2);
      else graph.max_flow(i, s, f, 2);
      //graph.max_flow(s, t);
    }
  }

  //assert(ans.size() == K);

  rep(i, K) cout << ans[i]+1 << endl;

  return 0;
}
