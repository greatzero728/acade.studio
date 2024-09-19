#include<bits/stdc++.h>

using namespace std;

int n, k;
vector<int> a, ans = {0};

int main(){
    scanf("%d %d", &n, &k);
    a = vector<int>(n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(a.begin(), a.end());
    while(k--){
        printf("%d", ans.size());
        for(auto d: ans) printf(" %d", a[d]);
        printf("\n");
        
        if(ans.back() == n - 1 or ans.back() + 1 == ans[ans.size() - 2]) ans.push_back(0);
        else ans.back()++;
    }
}