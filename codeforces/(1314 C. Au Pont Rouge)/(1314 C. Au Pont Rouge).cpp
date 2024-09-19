#include<bits/stdc++.h>
using namespace std;
const long long mx=1001;
long long lc[mx][mx],n,m,k,dp[mx][mx],ans=0; 
char s[mx]; 
vector<pair<long long,long long>> v;

int main() {
    cin>>n>>m>>k>>s;
    for (long long i=n;i;i--) for (long long j=n;j;j--) if (s[i-1]==s[j-1]) lc[i][j]=lc[i+1][j+1]+1;
    for (long long i=1;i<=n;i++) for (long long j=i;j<=n;j++) v.emplace_back(i,j);
    auto get_val=[&](long long len,pair<long long,long long> p){
        return len==p.second-p.first+1?0:s[p.first+len-1];
    };
    sort(v.begin(),v.end(),[&](pair<long long,long long> a,pair<long long,long long> b){
        long long l=min(lc[a.first][b.first],min(a.second-a.first+1,b.second-b.first+1)),l1=get_val(l,a),l2=get_val(l,b);
        return l1<l2;
    });
    for (long long l=0,r=v.size()-1;r>=l;){
        long long md=(l+r)/2;
        memset(dp,0,sizeof(dp)),dp[0][0]=1;
        for (long long i=1;i<=m;i++){
            for (long long j=1;j<=n;j++){
                long long e=-1,ln=min(lc[j][v[md].first],min(n-j+1,v[md].second-v[md].first+1));
                long long l1=ln==n-j+1?0:s[j+ln-1],l2=ln==v[md].second-v[md].first+1?0:s[v[md].first+ln-1];
                if (l1>=l2) e=ln==v[md].second-v[md].first+1?j+ln-1:j+ln;
                if (e!=-1) dp[i][e]+=dp[i-1][j-1];
                dp[i][e]=min(dp[i][e],(long long)1e18);
            }
            for (long long j=1;j<=n;j++) dp[i][j]=min(dp[i][j]+dp[i][j-1],(long long)1e18);
        }
        if (dp[m][n]>=k) l=md+1,ans=md; else r=md-1;
    }
    for (long long i=v[ans].first;i<=v[ans].second;i++) cout<<s[i-1];
    cout<<endl;
    return 0;
}