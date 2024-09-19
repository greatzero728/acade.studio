#include<bits/stdc++.h>
using namespace std;

int convexF(int x) {
    return x*x+1000000;
}
int concaveF(int x) {
    return -x*x-1000000;
}

int main() {
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>>res;
    if(m==3) {
        if(n>4) {
            cout << -1 << endl;
            return 0;
        }
        res.push_back({0,0});
        res.push_back({3,0});res.push_back({0,3});
        if(n==4) res.push_back({1,1});
        for(auto x:res) cout << x.first << " " << x.second << endl;
        return 0;
    }
    for(int i=1;i<=n;i++) {
        if(i<=m) res.push_back({i,convexF(i)});
        else res.push_back({i,concaveF(i)});
    }
    for(auto x:res) cout << x.first << " " << x.second << endl;
    return 0;
}