#include<bits/stdc++.h>

using namespace std;

int main() {
    string s, t;
    cin>>s>>t;
    int n = s.size();
    map<char, char> mp;
    for(int i = n; i--; ) if(s[i] != t[i]) {
        if(mp.find(s[i]) == mp.end()) {
            if(mp.find(t[i]) == mp.end()) {
                mp[s[i]] = t[i], mp[t[i]] = s[i];
            }
            else if(mp[t[i]] != s[i]) puts("-1"), exit(0);
        }
        else if(mp[s[i]] != t[i]) puts("-1"), exit(0);
    }
}