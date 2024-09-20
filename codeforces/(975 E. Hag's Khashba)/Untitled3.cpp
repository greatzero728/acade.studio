#include <iostream>
#include <vector>
#include <complex>
#include <iomanip>
#include <numeric>
using namespace std;

using cd = complex<long  double>;

int main(){
    int n, q;
    cin >> n >> q;
    vector<cd> v(n);
    for(auto& x : v){
        long double p, q;
        cin >> p >> q;
        x = cd { p, q }; }

    cd delta = v[0];
    for(auto& x : v) x -= delta;

    cd cog = 0;
    long double area = 0;
    for(int i = 0, j = 1; i < n; ++i, ++j,j %= n){
        area += imag(v[i] * conj(v[j])) / 2.0; }
    for(int i = 0, j = 1; i < n; ++i, ++j,j %= n){
        cog += (v[i] + v[j]) * (imag(v[i] * conj(v[j])) / (6.0 * area)); }

    cd a = 1, b = 0;
    int p1 = 0, p2 = 1;
    for(int i = 0; i < q; ++i){
        int t;
        cin >> t;
        if(t == 1){
            int s, f;
            cin >> s >> f;
            --s, --f;

            auto vp = v[p1 ^ p2 ^ s];
            auto fix = v[p1 ^ p2 ^ s] * a + b;

            // (x - vp) * (i | v[p] - cog| / (v[p] - cog)) + fix;
            a = cd { 0, abs(vp - cog) } / (vp - cog);
            b = (-vp) * cd { 0, abs(vp - cog) } / (vp - cog) + fix;

            if(p1 == s) p1 = f;
            else p2 = f; }
        else{
            int p;
            cin >> p;
            --p;
            auto r = a * v[p] + b + delta;
            cout << fixed << setprecision(10) << r.real() << ' ' << r.imag() << '\n'; } }
    return 0; }
            
