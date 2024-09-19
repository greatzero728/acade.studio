#include <bits/stdc++.h>

using namespace std;

//#define MULTITEST

#define x first
#define y second
#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define sz(a) int(a.size())
#define all(a) a.begin(), a.end()
#define forn(i, n) for(int i = 0; i < int(n); i++) 
#define fore(i, l, r) for(int i = int(l); i < int(r); i++)

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template <class A, class B> ostream& operator << (ostream& out, const pair<A, B> &a) {
	return out << "(" << a.x << ", " << a.y << ")";
}

template <class A> ostream& operator << (ostream& out, const vector<A> &v) {
	out << "[";
	forn(i, sz(v)) {
		if(i) out << ", ";
		out << v[i];
	}
	return out << "]";
}

mt19937 rnd(time(NULL));

const int INF = int(1e9);
const li INF64 = li(1e18);
const int MOD = int(1e9) + 7;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);

const int N = 100 + 7;
const int M = 30 * 24 * 60 + 13;

struct stud{
	int tp, t, c, i;
};

int n, m, k;
map<string, int> to;
int pr[N];
pt seg[4];
stud a[N];

bool read () {
	if (scanf("%d%d%d", &m, &n, &k) != 3)
		return false;
	to.clear();
	static char buf[100];
	forn(i, m){
		scanf("%s", buf);
		to[buf] = i;
	}
	forn(i, m){
		scanf("%d", &pr[i]);
	}
	forn(i, 4){
		int a, b, c, d;
		scanf("%d:%d-%d:%d", &a, &b, &c, &d);
		seg[i] = mp(a * 60 + b, c * 60 + d);
	}
	forn(i, n){
		int d, t1, t2;
		scanf("%s %d %d:%d %d", buf, &d, &t1, &t2, &a[i].c);
		--d;
		a[i].tp = to.count(buf) ? to[buf] : -1;
		a[i].t = d * 24 * 60 + t1 * 60 + t2;
		a[i].i = i;
	}
	return true;
}

int dp[N][M];
pt p[N][M];
int nxt[N][M];
bool ok[N][M];

bool in(int x){
	forn(i, 4) if (seg[i].x <= x % (24 * 60) && x % (24 * 60) <= seg[i].y)
		return true;
	return false;
}

void solve() {
	sort(a, a + n, [](const stud &a, const stud &b){
		return a.t < b.t;
	});
	int tot = 24 * 60 * k;
	forn(i, m){
		int k = 0, cnt = 0;
		forn(j, tot){
			while (k < tot && cnt < pr[i]){
				cnt += !in(k);
				++k;
			}
			ok[i][j] = cnt == pr[i];
			nxt[i][j] = k;
			cnt -= !in(j);
		}
	}
	forn(i, n + 1) forn(j, tot + 1) dp[i][j] = -INF;
	dp[0][0] = 0;
	forn(i, n + 1) forn(j, tot + 1) if (dp[i][j] >= 0){
		if (i < n && dp[i + 1][j] < dp[i][j]){
			dp[i + 1][j] = dp[i][j];
			p[i + 1][j] = mp(i, j);
		}
		if (j < tot && dp[i][j + 1] < dp[i][j]){
			dp[i][j + 1] = dp[i][j];
			p[i][j + 1] = mp(i, j);
		}
		if (i < n && j < tot && a[i].tp != -1 && !in(j) && ok[a[i].tp][j] && nxt[a[i].tp][j] - 1 < a[i].t && dp[i + 1][nxt[a[i].tp][j]] < dp[i][j] + a[i].c){
			dp[i + 1][nxt[a[i].tp][j]] = dp[i][j] + a[i].c;
			p[i + 1][nxt[a[i].tp][j]] = mp(i, j);
		}
	}
	vector<pair<int, pt>> res;
	int i = n, j = tot;
	while (i > 0 || j > 0){
		int ni = p[i][j].x, nj = p[i][j].y;
		if (ni != i && nj != j)
			res.pb(mp(ni, mp(nj, j - 1)));
		i = ni, j = nj;
	}
	reverse(all(res));
	printf("%d\n%d\n", dp[n][tot], sz(res));
	for (auto it : res)
		printf("%d %d %02d:%02d %d %02d:%02d\n", a[it.x].i + 1, it.y.x / (24 * 60) + 1, it.y.x % (24 * 60) / 60, it.y.x % (24 * 60) % 60, it.y.y / (24 * 60) + 1, it.y.y % (24 * 60) / 60, it.y.y % (24 * 60) % 60);
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	
	int tt = clock();
	
#endif
	
	cerr.precision(15);
	cout.precision(15);
	cerr << fixed;
	cout << fixed;

#ifdef MULTITEST
	int tc;
	scanf("%d", &tc);
	while(tc--){
		read();
#else
	while(read()) {	
#endif
		solve();
		
#ifdef _DEBUG
	cerr << "TIME = " << clock() - tt << endl;
	tt = clock();
#endif

	}
}