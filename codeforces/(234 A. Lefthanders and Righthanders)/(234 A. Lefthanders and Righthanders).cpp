#include <bits/stdc++.h>

using namespace std;

char s[121];

void print(int a, int b) {
	if(s[a] == 'R' && s[b] == 'L') swap(a, b);
	printf("%d %d\n", a, b);
	return;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n; scanf("%d %s", &n, s + 1);
	
	for(int i = 1; i <= n >> 1; i++) {
		print(i, i + (n >> 1));
	}
	return 0;
}
