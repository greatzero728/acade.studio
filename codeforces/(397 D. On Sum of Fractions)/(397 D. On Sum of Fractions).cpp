#include<bits/stdc++.h>
using namespace std;

bool prime(long long a){
	if(a < 4)return a == 2 || a == 3;
	for(long long i = 2; i * i <= a; i++){
		if(a % i == 0) return false;
	}
	return true;
}

long long gcd(long long a , long long b) {
	if(b == 0)return a;
	return gcd(b , a % b);
}
int main(){
	int t;cin>>t;
	while(t--){
		long long v , u;cin>>v;
		long long intial = v;
		u = v + 1;
		while(!prime(u)) u++;
		while(!prime(v)) v--;
		long long numberator = v * (u - 2) - (2 * (u - 1 - intial));
		long long denmurator = 2 * v * u;
		long long g = __gcd(numberator, denmurator);

		cout << numberator / g << '/' << denmurator / g << '\n';

	}
}
