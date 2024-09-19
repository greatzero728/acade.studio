#include<bits/stdc++.h>

const int mod = 1e9+7;
int n, m, seed, vmax;

auto rnd() {
	int ret = seed;
	seed = (seed * 7LL + 13) % mod;
	return ret;
}

void divide(std::map<int, long long>& mp, int idx) {
	auto it = std::prev(mp.upper_bound(idx));

	if (it->first != idx)// the index was not the left border
		// set it as a border
		mp[idx] = it->second;
}

int binaryExp(int a, int b, int p) {
	int res = 1 % p;
	for (; b; b /= 2, a = 1LL * a * a % p) {
		if (b % 2) {
			res = 1LL * res * a % p;
		}
	}
	return res;
}

signed main() {

	std::cin >> n >> m >> seed >> vmax;

	std::vector<int>a(n);
	std::map<int, long long>f;

	for (int i = 0; i < n; i++) {
		a[i] = rnd() % vmax + 1;
		f[i] = a[i];
	}

	f[n] = -1;

	while (m--) {
		int op = 1 + (rnd() % 4);
		int l = 1 + (rnd() % n);
		int r = 1 + (rnd() % n);

		if (l > r)std::swap(l, r);
		l--;
		int x;
		if (op == 3)
			x = rnd() % (r - l);
		else
			x = rnd() % vmax + 1;

		divide(f, l);
		divide(f, r);
		if (op == 1) {
			// iterate over all left borders in range, and increase them by x
			for (auto it = f.find(l); it->first != r; it++) {
				it->second += x;
			}

		}
		else if (op == 2) {
			//erase all left borders presented in the range, and then add new left border with new value x
			for (auto it = f.find(l); it->first != r; it = f.erase(it))
				;
			f[l] = x;
		}
		else if (op == 3) {
			std::vector<std::pair<long long, long long>> v; // to store the value with its frequency
			for (auto it = f.find(l); it->first != r; it++) {
				int frequency = std::next(it)->first - it->first;
				v.push_back({ it->second, frequency});
			}

			std::sort(v.begin(), v.end()); 
			for (auto [a, b] : v) {
				if (x < b) { // here, we passed the x smallest value.
					std::cout << a << "\n";
					break;
				}
				x -= b;
			}
		}
		else if (op == 4) {
			int y = rnd() % vmax + 1;
			int ans = 0;
			for (auto it = f.find(l); it->first != r; it++) {
				int fr = (std::next(it)->first - it->first);
				ans = (ans + 1LL * fr * binaryExp(it->second % y, x, y)) % y;
			}
			std::cout << ans << "\n";
		}
	}
}