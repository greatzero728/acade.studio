#include <bits/stdc++.h>
using namespace std;
string s;

int main() {
	cin >> s;
	int pos;
	for (pos = 0; s[pos] != '.'; pos++);
	if (s[pos - 1] == '9') {
		cout << "GOTO Vasilisa.\n";
		return 0;
	}
	if (s[pos + 1] >= '5') s[pos - 1] ++;
	for (int i = 0; i < pos; i++) cout << s[i];
}