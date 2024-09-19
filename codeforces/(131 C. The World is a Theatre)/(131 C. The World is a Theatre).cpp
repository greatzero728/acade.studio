#include <iostream>
#include <cstring>
using namespace std; 

long long dp[31][31];
long long combination(long long n,long long r)
{
    if (n < r)return 0;
    if (n == 1)return 1;
    if (r == 1)return n;
    if(dp[n][r]!=-1)
        return dp[n][r];
    return dp[n][r]=combination(n - 1, r - 1) + combination(n - 1, r); 
}
int main(){
    long long n,m,t;
    cin>>n>>m>>t;
    memset(dp,-1,sizeof(dp));
    long long ans=0;
    for(long long boys=4;boys<=n;boys++){
        if(boys<t){
            long long girls=t-boys;
            if(girls<=m){
                ans+=combination(n,boys)*combination(m,girls);
            }
        }
    }
    cout<<ans<<endl;
}