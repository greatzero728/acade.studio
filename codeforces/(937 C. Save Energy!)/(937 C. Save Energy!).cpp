#include<bits/stdc++.h>
using namespace std;

int main() {
    long long k, d, t; cin>>k>>d>>t;
    long long s = t * 2;
    long long p = (k + d - 1) / d * d;
    long long sub = p + k;
    long long num = s / sub;
    long long remain = s % sub;
    if(remain > 2 * k) {
        cout << fixed << setprecision(10) << (double)(num * p + remain - k) << endl;
    } else {
        cout << fixed << setprecision(10) << (double)(num * p + remain / 2.0) << endl;
    }
}