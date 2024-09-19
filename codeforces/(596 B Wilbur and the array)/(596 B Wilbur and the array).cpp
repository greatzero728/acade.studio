#include<bits/stdc++.h>

using namespace std;

long long n, ans, p;

int main() {
	for(cin>>n; cin>>n;) {
		ans += abs(n - p), p = n;
	}
	cout<<ans;
	return 0;
}