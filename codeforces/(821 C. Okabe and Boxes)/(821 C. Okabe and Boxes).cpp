#include<bits/stdc++.h>

using namespace std;

int main() {
    int n; scanf("%d", &n);
    
    stack<int> st;
    int desiredValue = 0;
    int ans = 0;
    for(int i = n + n; i--; ) {
        string s; cin>>s;
        if(s == "add") {
            int x; scanf("%d", &x);
            st.push(x);
        }
        else {
            desiredValue++;
            if(st.empty()) continue;
            if(st.top() == desiredValue) st.pop();
            else st = stack<int>(), ans++;
        }
    }
    cout<<ans;
}