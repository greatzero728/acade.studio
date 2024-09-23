#include <bits/stdc++.h>
using namespace std;
int n,V;
int a[21],b[21];
double best;
bool ok(double mid){
    double tot=0;
    for (int i = 0; i <n ; ++i) {
        if(mid*a[i]>b[i]) return false;
        tot+=mid*a[i];
    }
    if(tot>V)
        return false;
    best=tot;
    return true;
}
int main() {
    cin>>n>>V;
    for (int i = 0; i <n ; ++i) cin>>a[i];
    for (int i = 0; i <n ; ++i) cin>>b[i];
    double l=0,r=V;
    for (int i = 0; i <100 ; ++i) {
        double mid=(l+r)/2;
        if(ok(mid))
            l=mid;
        else r=mid;
    }
    cout<<fixed<<setprecision(4)<<best<<'\n';
}