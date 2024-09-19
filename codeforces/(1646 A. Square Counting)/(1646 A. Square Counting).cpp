#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        long long s;
        cin >> n >> s;
        cout << s / (1LL * n * n) << endl;
    }
}