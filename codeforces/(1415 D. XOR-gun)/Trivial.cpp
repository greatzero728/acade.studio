// LUOGU_RID: 116068520
#include <bits/stdc++.h>
using namespace std;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int n,ans=1e9;
	cin>>n;
	vector<int> a(n);
	for(int&x:a) cin>>x;
	for(int i=0;i<n;i++){
		int s=a[i];
		for(int j=i+1;j<n&&j<i+32;j++){
			int t=0;
			for(int k=j;k<n&&k<i+32;k++) if((t^=a[k])<s) {ans=min(ans,k-i-1);break;}
			s^=a[j];
		}
	}
	cout<<(ans>n?-1:ans);
	return 0;
}