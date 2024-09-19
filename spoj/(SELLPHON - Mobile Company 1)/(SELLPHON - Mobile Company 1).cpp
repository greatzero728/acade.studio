#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int L, M, N;
		cin >> L >> M >> N;
		vector<int> S(N);
		for (int i = 0; i < N; i++) {
			cin >> S[i];
		}
		vector<string> map(M);
		for (int i = 0; i < M; i++) {
			cin >> map[i];
		}
		vector<pair<int, int>> shops;
		for (int i = 0; i < N; i++) {
			shops.push_back({S[i], i});
		}
		sort(shops.begin(), shops.end(), greater<pair<int, int>>());
		vector<int> sold(M, 0);
		for (auto shop : shops) {
			int index = shop.second;
			for (int i = 0; i < M; i++) {
				if (map[i][index] == 'Y') {
					sold[i] += shop.first;
					break;
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < M; i++) {
			ans += min(L, sold[i]);
			L -= min(L, sold[i]);
		}
		cout << ans << endl;
	}
	return 0;
}