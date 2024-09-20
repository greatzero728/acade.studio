#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t,n,k; cin>>t;
    while(t--){
        cin>>n>>k;
        if((n+1)/2<k) cout<<"-1\n";
        else {
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(i==j&&i%2==0&&k){
                        cout<<'R';
                        k--;
                    }
                    else{
                        cout<<'.';
                    }

                }
                cout<<'\n';
            }
        }

    }
  return 0;
 }