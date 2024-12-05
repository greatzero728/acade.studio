#include <bits/stdc++.h>
using namespace std;
string s;
int mem[11][11][2][2];
int vis[11][11][2][2],vid;
int solution(int i,int cnt,bool f,bool st,int &curDigit){
    if(i==s.size())
        return cnt;
    int &ret=mem[i][cnt][f][st];
    if(vis[i][cnt][f][st]==vid)
        return ret;
    vis[i][cnt][f][st]=vid;
    ret=0;
    for (int j = 0; j <=(f?9:(s[i]-'0')) ; ++j) {
        ret+=solution(i+1,cnt+(j==curDigit&&(st||j)),f|(j<s[i]-'0'),
                 st|j,curDigit);
    }
    return ret;
}
array<int,10> getAnswer(int x){// number of digit from 1 to x
    s= to_string(x);
    array<int,10>res;
    for (int i = 0; i <10 ; ++i) {
        ++vid;
        res[i] = solution(0, 0, 0, 0, i);
    }
    return res;
}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r,l;
    while(cin>>l>>r,l&&r) {
        if(l>r) swap(l,r);
        array<int, 10> to_r = getAnswer(r);
        array<int, 10> to_l = getAnswer(l - 1);
        for (int i = 0; i < 10; ++i) {
            cout << to_r[i] - to_l[i] << ' ';
        }
        cout<<'\n';
    }
}