#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using db = double;
#define pb push_back

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T> using rset = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;

rset<ll> s;

void flip(ll x) {
	if (s.find(x) != s.end())
		s.erase(x);
	else
		s.insert(x);
}

int test(ll x) {
	return s.order_of_key(*prev(s.upper_bound(x))) & 1;
}

void Set(ll l, ll r, int val) {
	int vr = test(r);
	if (test(l) != val)
		flip(l);
	while (*s.upper_bound(l) < r)
		s.erase(s.upper_bound(l));
	if (test(r) != vr)
		flip(r);
}

ll mex() {
	if (*next(s.begin()) > 1)
		return 1;
	return *next(next(s.begin()));
}

int main() {
	s.insert(0);
	s.insert(LLONG_MAX / 2);
	int q;
	cin >> q;
	while (q--) {
		int op;
		ll l, r;
		scanf("%d%lld%lld", &op, &l, &r);
		if (op == 3) {
			flip(l);
			flip(r + 1);
		} else {
			Set(l, r + 1, op == 1 ? 1 : 0);
		}
		printf("%lld\n", mex());
	}
	return 0;
}