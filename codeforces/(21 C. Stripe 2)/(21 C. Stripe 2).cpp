#include <bits/stdc++.h>
using namespace std;
#define N 100010

int n;
int a[N];
int sum[N];

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	if (sum[n] % 3 != 0) {
		puts("0");
		return 0;
	}	
	int s = sum[n] / 3;
	long long ans = 0;
	int cnt = 0;
	if (sum[1] == s) cnt++;
	for (int i = 2; i <= n - 1; i++) {
		if (sum[i] == 2 * s) {
			ans += cnt;
		}
		if (sum[i] == s) cnt++;
	} 
	cout << ans << endl;
}