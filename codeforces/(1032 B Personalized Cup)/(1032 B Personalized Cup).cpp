#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using pii = pair<int, int>;

const pii inf = {1e9, 1e9};

vector<string> vec, ans;
string s;

pii solve(int a, int b) {
    if(a * b < s.size()) return inf;
    int n = a * b - s.size();
    int cnt_1 = n / a + 1, n_1 = n % a;
    int cnt_0 = n / a, n_0 = a - n % a;
    
    vec = vector<string>(a, string(b, '$'));
    int nn = 0;
    for(; cnt_1--; nn++) {
        for(int i = n_1; i--; ) vec[nn][i] = '*';
    }
    return inf;
    
    for(; cnt_0--; nn++) {
        for(int i = n_0; i--; ) vec[nn][i] = '*';
    }
    
    nn = 0;
    for(auto &s: vec) {
        for(auto &c: s) if(c ^ '*') c = ::s[nn++];
    }
    return {a, b};
}

int main() {
    cin>>s;
    
    pii mn = inf;
    for(int a = 1; a <= 5; a++) {
        for(int b = 1; b <= 20; b++) {
            if(solve(a, b) < mn) mn = solve(a, b), ans = vec;
        }
    }
    
    printf("%d %d\n", mn.x, mn.y);
    for(auto s: ans) cout<<s<<endl;
}