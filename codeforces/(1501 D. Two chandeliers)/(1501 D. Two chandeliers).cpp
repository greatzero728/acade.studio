#include <bits/stdc++.h>
using namespace std;
#define N 500010
#define ll long long

ll n, m;
ll p, q, r, d, inv, l;
ll k;
ll a[N], b[N];
ll pos[N * 2];

vector <pair <int, int> > v;

long long int read_int(){
	char r;
	bool start=false,neg=false;
	long long int ret=0;
	while(true){
		r=getchar();
		if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
			continue;
		}
		if((r-'0'<0 || r-'0'>9) && r!='-' && start){
			break;
		}
		if(start)ret*=10;
		start=true;
		ret+=r-'0';
	}
	return ret;
}

ll check(ll D) {
	ll rt = D;
	for (int t = 0; t < v.size(); t++) {
		int i = v[t].first;
		int j = v[t].second;
		if ((i - j) % p) continue;
		d = (i - j) / p;
		l = ((- d * inv % r) + r) % r;
		ll pqr = p * q * r;
		l = (l * n + i) % pqr;
		rt -= D / pqr;
		if (l != 0 && l <= D % pqr) rt --;
	}
	return rt >= k;
}
 
int main(){
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) a[i] = read_int();
	for (int i = 1; i <= m; i++) b[i] = read_int(), pos[b[i]] = i;
	for (int i = 1; i <= n; i++) {
		if (pos[a[i]]) {
			v.push_back({i, pos[a[i]]});
		}
	}
	p = __gcd(n, m);
	q = n / p;
	r = m / p;
	for (int i = 1; i < r; i++) {
		if (q * i % r == 1) {
			inv = i;
			break;
		}
	}
	
	ll lo = 0, hi = 1e18;
	while (lo + 1 < hi){
		ll mi = (lo + hi) / 2;
		if (check(mi)) hi = mi;
		else lo = mi;
	}
	cout << hi << endl;
}