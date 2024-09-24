#include<bits/stdc++.h>
#define rep(i,n)for(int i=0;i<(n);i++)
using namespace std;
typedef long long ll;

ll dp[100001], bit[100001];
int x[100000], n;
void update(int k, ll x) {
	while (k <= n) {
		bit[k] = max(bit[k], x);
		k += k&-k;
	}
}
ll query(int k) {
	ll ans = 0;
	while (k) {
		ans = max(ans, bit[k]);
		k -= k&-k;
	}
	return ans;
}
int main() {
	scanf("%d", &n);
	ll sum = 0;
	rep(i, n)scanf("%d", &x[i]), sum += x[i];
	rep(i, n){
		dp[i] = query(x[i]) + x[i];
		update(x[i], dp[i]);
	}
	printf("%lld\n", sum - query(n));
}
