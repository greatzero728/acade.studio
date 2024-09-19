#include <bits/stdc++.h>
using namespace std;
int main(){

    int n; cin >> n;
    vector<int> a(n);
    vector<int> loc_ptr(n+1);
    vector<vector<int>> loc(n + 1);

    for(int i = 0;  i < n; i ++){
        cin >> a[i];
        loc[a[i]].emplace_back(i);
    }

    vector<unsigned int> r(n + 1);
    mt19937 twister(chrono::steady_clock::now().time_since_epoch().count());

    for(int i  = 0 ; i <= n; i++) {
        r[i] = twister();
    }

    map<unsigned long long, int> hashes;
    hashes[0] = 1;
    vector<int> freq(n + 1);
    vector<int> freq2(n + 1);
    int ans = 0;
    vector<unsigned long long> hash(n + 5);
    int from = 0;
    for(int i = 0; i < n; i++) {
        if(freq2[a[i]] >= 3) {
            for(int till = loc[a[i]][loc_ptr[a[i]]]; from <= till; ++from) {
                hashes[hash[from]]--;
            }
            ++loc_ptr[a[i]];

        }
        hash[i+1] = hash[i];
        if(freq[a[i]] == 2) {
            // subtract twice instead of multiplying by two to avoid overflow
            hash[i + 1] -= r[a[i]];
            hash[i + 1] -= r[a[i]];
        }
        else {
            hash[i + 1] += r[a[i]];
        }
        freq[a[i]]++;
        freq[a[i]] %= 3;
        freq2[a[i]]++;
        ans += hashes[hash[i + 1]];
        hashes[hash[i + 1]]++;
    }
    cout << ans << endl;

}