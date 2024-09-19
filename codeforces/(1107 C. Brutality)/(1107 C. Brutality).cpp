#include <bits/stdc++.h>
using namespace std;
#define N 200010

int n, k;
int a[N];
string s;

long long maxSum(vector <int> &v) {
	sort (v.begin(), v.end());
	reverse (v.begin(), v.end());
	long long rt = 0;
	for (int i = 0; i < k && i < v.size(); i++) {
		rt += v[i];
	}
	return rt;
}

int main(){
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> a[i];
	cin >> s;
	char c = s[0];
	vector <int> v;
	long long sum = 0;
	v.push_back(a[0]);
	for (int i = 1; i < n; i++) {
		if (s[i] == c) v.push_back(a[i]);
		else {
			sum += maxSum(v);
			v.clear();
			v.push_back(a[i]);
			c = s[i];
		}
	}
	sum += maxSum(v);
	cout << sum << endl;
}