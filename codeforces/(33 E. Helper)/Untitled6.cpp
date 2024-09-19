#include <bits/stdc++.h>

#ifdef LOCAL
	#define debug(x) cerr << (#x) << ": " << x << endl
#else
	#define debug(x) ;
#endif

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rep1(i, n) for (int i = 1; i < (n); ++i)
#define rep1n(i, n) for (int i = 1; i <= (n); ++i)
#define repr(i, n) for (int i = (n) - 1; i >= 0; --i)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(a) (int)(a.size())
#define each(x, a) for (auto &x : a)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using str = string;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pair<int, int>>;
using vvi = vector<vi>;

const int BIG = 1e9, LG = 30, maxN = 1e2, SZ1 = 24 * 60, SZ2 = 30 * 60 * 24;
const ll INF = 1e18;

struct Item {
	str s;
	int end, c, id;
	friend istream& operator>>(istream& is, Item& a) {
		int d;
		str s;
		is >> a.s >> d >> s >> a.c;
		a.end = (d - 1) * 24 * 60 + ((s[0] - '0') * 10 + (s[1] - '0')) * 60 + (s[3] - '0') * 10 + (s[4] - '0');
		return is;
	}
	bool operator<(const Item& other) const {
		return end < other.end;
	}
} a[maxN];

struct Elem {
	int id, start, end;
	Elem(int id = 0, int start = 0, int end = 0) : id(id), start(start), end(end) {}
	friend ostream& operator<<(ostream& os, Elem& e) {
		os << e.id << " " << e.start / SZ1 + 1 << " ";
		int temp = e.start % SZ1;
		os << temp / 600 << temp / 60 % 10 << ":" << temp % 60 / 10 << temp % 10 << " ";
		os << e.end / SZ1 + 1 << " ";
		temp = e.end % SZ1;
		os << temp / 600 << temp / 60 % 10 << ":" << temp % 60 / 10 << temp % 10;
		return os;
	}
};

bool used[SZ1];
int test = 1, m, n, k, t[maxN], dp[SZ2][maxN + 1], cur;
str s;
unordered_map<str, int> dict;
vector<Elem> ans;

void solve() {
	rep(i, SZ2) {
		fill(dp[i], dp[i] + maxN + 1, 0);
	}
	cin >> m >> n >> k;
	dict.clear();
	rep(i, m) {
		cin >> s;
		dict[s] = i;
	}
	rep(i, m) {
		cin >> t[i];
	}
	fill(used, used + SZ1, false);
	rep(i, 4) {
		cin >> s;
		int start = ((s[0] - '0') * 10 + (s[1] - '0')) * 60 + (s[3] - '0') * 10 + (s[4] - '0');
		int end = ((s[6] - '0') * 10 + (s[7] - '0')) * 60 + (s[9] - '0') * 10 + (s[10] - '0');
		for (int j = start; j <= end; j++)
			used[j] = true;
	}
	rep(i, n) {
		cin >> a[i];
		a[i].id = i;
	}
	sort(a, a + n);
	rep(i, n) {
		rep(j, SZ2) {
			dp[j][i + 1] = dp[j][i];
		}
		if (dict.find(a[i].s) == dict.end())
			continue;
		int r = a[i].end, l = r, temp = t[dict[a[i].s]];
		for (int j = 0; j < temp && l >= 0; j++) {
			l--;
			while (l >= 0 && used[l % SZ1])
				l--;
		}		
		while (l >= 0) {
			dp[r][i + 1] = max(dp[r][i + 1], dp[l][i] + a[i].c);
			r--;
			if (!used[r % SZ1]) {
				l--;
				while (l >= 0 && used[l % SZ1])
					l--;
			}
		}
		rep1(j, SZ2) {
			dp[j][i + 1] = max(dp[j][i + 1], dp[j - 1][i + 1]);
		}
	}
	cout << dp[SZ2 - 1][n] << "\n";
	ans.clear();
	cur = SZ2 - 1;
	repr(i, n) {
		if (dp[cur][i + 1] == 0)
			break;
		if (dp[cur][i + 1] == dp[cur][i])
			continue;
		while (cur > 0 && dp[cur - 1][i + 1] == dp[cur][i + 1])
			cur--;
		int r = cur, l = cur, temp = t[dict[a[i].s]];
		for (int j = 0; j < temp && l >= 0; j++) {
			l--;
			while (l >= 0 && used[l % SZ1])
				l--;
		}
		r--;
		while (r >= 0 && used[r % SZ1])
			r--;
		ans.eb(a[i].id + 1, l, r);
		cur = l;
	}
	reverse(all(ans));
	cout << sz(ans) << "\n";
	each(i, ans) {
		cout << i << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
		cin >> test;
	#endif
	while (test--)
		solve();
	return 0;
}