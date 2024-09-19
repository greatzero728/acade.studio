#include <bits/stdc++.h>

using namespace std;

const long long mod=998244353;
long long add(long long a,long long b){
    return ((a%mod)+(b%mod))%mod;
}
long long mul(long long a,long long b){
    return (a%mod)*(b%mod)%mod;
}
long long sub(long long a,long long b){
    long long ret=((a%mod)-(b%mod))%mod;
    if(ret<0)ret+=mod;
    return ret;
}
long long power(long long a,long long b){
    if(b==0)return 1;
    if(b==1)return a%mod;
    long long r=power(a,b/2);
    if(b&1){
        return mul(mul(r,r),a);
    }
    else{
        return mul(r,r);
    }
}
long long divide(long long a,long long b){
    return mul(a,power(b,mod-2));
}
const int N=2e5+5;
long long factorial[N];
long long nCr(long long n,long long r){
    return divide(factorial[n],mul(factorial[r],factorial[n-r]));
}
int main(){
    factorial[0]=1;
    for(int i=1;i<N;i++)factorial[i]=mul(factorial[i-1],i);
    int n,k;
    cin>>n>>k;
    vector<int>h(n+1);
    for(int i=1;i<=n;i++)
        cin>>h[i];
    int o=0;
    for(int i=1;i<=n;i++){
        if(h[i%n+1]==h[i])o++;
    }
    long long ans=power(k,o);
    long long sum=0;
    for(int m=0;m<=n-o-1;m++){
        long long x=mul(power(k-2,m),nCr(n-o,m));
        long long y=0;
        if((n-o-m)&1){
            y=divide(power(2LL,n-o-m),2);
        }
        else{
            y=sub(divide(power(2LL,n-o-m),2),divide(nCr(n-o-m,(n-o-m)/2),2));
        }
        sum=add(sum,mul(x,y));
    }
    ans=mul(ans,sum);
    cout<<ans<<endl;
}