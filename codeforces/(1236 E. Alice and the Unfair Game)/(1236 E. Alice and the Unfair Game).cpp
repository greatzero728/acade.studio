//#include<cstdio>
#include <iostream>
//#include<algorithm>
using namespace std;
int n,m,a[300100];
int L[300100],R[300100];
const int T=1e5;
int main(){
    cin>>n>>m;
    if(n == 1)
    {
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<=m;i++)
        cin>>a[i];
    for(int i=m;i>=1;i--){
        L[i+a[i]+T]=L[i+a[i]+1+T]+1;
        R[a[i]-i+T]=R[a[i]-i-1+T]+1;
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        int l=max(1,i-(m+1)+L[i+T]),r=min(n,i+(m+1)-R[i+T]);
        ans+=1ll*(r-l+1);
    }
    cout<<ans<<endl;
}