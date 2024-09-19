#include <bits/stdc++.h>

using namespace std;

#define int long long

const int maxN = 100*1000 + 5;
const int mod = 1000*1000*1000;

vector<int> l[maxN], r[maxN];
int mx[2][maxN];
int mi[2][maxN];
int mark[maxN];

void dfs(int v)
{
    mark[v] = 1;
    for(auto u : l[v])
    {
	  mi[0][v] = min(mi[0][v], min(mi[0][u], mi[1][u]));
	  mx[0][v] = max(mx[0][v], max(mx[0][u], mx[1][u]));
    }

    for(auto u : r[v])
    {
	  mi[1][v] = min(mi[1][v], min(mi[0][u], mi[1][u]));
	  mx[1][v] = max(mx[1][v], max(mx[0][u], mx[1][u]));
    }
}

set<int> se;
vector<int> ans;

void solve(int s, int e)
{
    if(e - s <= 0) return;

    int cur = *se.begin(); se.erase(cur);
//    cout << s << ' ' << e << endl;
    if(cur != s) { cout << "IMPOSSIBLE" << endl; exit(0); }
    if(e - s == 1) { ans.push_back(cur); return; }
    //   cout << s << ' ' << e << endl;

    mi[1][s] = min(mi[1][s], e);
   
 
    for(int i = s + 1; i <= mx[0][s]; i ++)
	  mx[0][s] = max(mx[0][s], max(mx[1][i], mx[0][i]));

    for(int i = e - 1; i >= mi[1][s]; i --)
	  mi[1][s] = min(mi[1][s], min(mi[0][i], mi[1][i]));

    if(mi[1][s] <= mx[0][s]) { cout << "IMPOSSIBLE" << endl; exit(0); }

//    cout << s << ' ' << e << ' ' << mi[0][s] << ' ' << mx[0][s] << ' ' << mi[1][s] << ' ' << mx[1][s] << endl;

    solve(s + 1, mx[0][s] + 1);
    ans.push_back(cur);
    solve(mx[0][s] + 1, e);
}


main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;

    for(int i = 0; i < n; i ++)
    {
	  mx[0][i] = mx[1][i] = i;
	  mi[0][i] = mi[1][i] = n;
    }

//    for(int i = 0; i < n; i ++)
//	  cout << mi[0][i] << ' ' << mx[0][i] << ' ' << mi[1][i] << ' ' << mx[1][i] << endl;

    //  cout << "----------" << endl;

    for(int i = 0; i < m; i ++)
    {
	  int v, u; string s; cin >> v >> u >> s; v --; u --;

	  if(v >= u) { cout << "IMPOSSIBLE" << endl; return 0; }

	  if(s == "RIGHT")
	  {
		r[v].push_back(u);
		mi[1][v] = min(mi[1][v], u);
		mx[1][v] = max(mx[1][v], u);
	  }
	  else
	  {
		l[v].push_back(u);
		mi[0][v] = min(mi[0][v], u);
		mx[0][v] = max(mx[0][v], u);
	  }
    }

    for(int i = 0; i < n; i ++) se.insert(i);

    for(int i = 0; i < n; i ++)
	  if(!mark[i]) dfs(i);

//    cout << mx[0][0] << endl;
    
//    for(int i = 0; i < n; i ++)
//	  cout << mi[0][i] << ' ' << mx[0][i] << ' ' << mi[1][i] << ' ' << mx[1][i] << endl;

//    cout << "---------------" << endl;
    solve(0, n);

//    cout << mx[0][0] << endl;

//    cout << "---------------" << endl;

//    for(int i = 0; i < n; i ++)
//	  cout << mi[0][i] << ' ' << mx[0][i] << ' ' << mi[1][i] << ' ' << mx[1][i] << endl;

    for(auto u : ans)
	  cout << u + 1 << ' '; cout << endl;

    return 0;
}
