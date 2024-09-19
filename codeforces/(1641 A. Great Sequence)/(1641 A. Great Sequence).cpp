#include<bits/stdc++.h>
using namespace std;
int main(){
    int t; cin>>t;
    while(t--){
        long long a,b; cin>>a>>b;
        long long c[a]; map<long long,long long> d;
        for(int i=0;i<a;i++) cin>>c[i],d[c[i]]++;
        sort(c,c+a);
        long long e=0;
        for(int i=0;i<a;i++) if(d[c[i]]) d[c[i]]--,d[b*c[i]]?d[b*c[i]]--:e++;
        cout<<e<<endl;
    }
}