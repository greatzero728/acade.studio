#define rnd (((((INT)rand() << 15) | rand()) << 15) | rand())
#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

int main() {
	freopen("in.txt", "w", stdout);
	
	srand(time(0));
	
	int t = 10;
//	t = 1;
	cout<<t<<endl;
	while(t--) {
		int n = rnd % 3000 + 1;
//		n = 6;
//		n = rnd % 5 + 1;
		cout<<n<<endl;
		for(int i = 1; i < n; i++) cout<<rnd % i + 1<<' '<<i + 1<<endl;
		puts("");
	}
	
	return 0;
}
