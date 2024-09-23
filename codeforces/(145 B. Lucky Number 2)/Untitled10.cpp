#include<bits/stdc++.h>
using namespace std;
int a1, a2, a3, a4;
string ans, ed, st;

int main() {
	scanf("%d%d%d%d", &a1, &a2, &a3, &a4);
	if(abs(a3 - a4) > 1) {
		printf("-1\n");
		return 0;
	}
	if(a3 > a4) {
		for(int i = 1; i <= a3; i++)
			ans += "47";
		a1 -= a3;
		a2 -= a3;
	}
	else if(a3 < a4) {
		st = "7";
		ans = "4";
		for(int i = 1; i <= a3 - 1; i++)
			ans += "74";
		ans += "7";
		ed = "4";
		a1 -= a4;
		a2 -= a4;
	}
	else {
		if(a1 == a3) {
			st = "7";
			for(int i = 1; i <= a3; i++)
				ans += "47";
			a1 -= a3;
			a2 -= a3 + 1;
		} else {
			for(int i = 1; i <= a3; i++)
				ans += "47";
			ed = "4";
			a1 -= a3 + 1;
			a2 -= a3;
		}
		
	}
	if(a1 < 0 || a2 < 0) {
		printf("-1");
		return 0;
	}
//	puts("1");	
	string now = "";
	for(int i = 1; i <= a1; i++) {
		now += '4';
	}
//	puts("1");
	for(int i = 1; i <= a2; i++) {
		ans += '7';
	}//
	cout << st << now << ans << ed;
//	for(int i = )
}

