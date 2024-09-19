#include <iostream>
#include <string>

using namespace std;

int main() {
	int n;
	int p = 0;
	int q = 0;
	string s;
	cin >> n >> s;
	for(int i = 0; i < n / 2; i++) {
		if(s[i] == '?') p ++;
		else q += s[i] - '0';
	}
	for(int i = n / 2; i < n; i++) {
		if(s[i] == '?') p --;
		else q -= (s[i] - '0');
	}

	if(p < 0) {
		p *= -1;
		q *= -1;
	}

	if(q == 9 * (-p / 2)) {
		cout << "Bicarp";
	}
	else {
		cout << "Monocarp";
	}
}