#include <bits/stdc++.h>

using namespace std;

int main() 
{
    int n;
    cin >> n;
    
    vector<string> guss(n), ans;
    vector<int> bulls(n), cows(n);

    for (int i = 0 ; i < n ; i++) 
    {
        cin >> guss[i] >> bulls[i] >> cows[i];
    }
    
    for (int x = 0 ; x < 1e4 ; x++)
    {
        string s = to_string(x);
        while (s.size() < 4) {
            s = "0" + s;
    	}
        
        set<char> S;
        for (auto &ch:s){
            S.insert(ch);
        }
        if (S.size() != 4) continue;
        
        bool flag = true;
        for (int i = 0 ; i < n ; i++) 
        {
            int b = 0, c = 0;
            for (int j = 0 ; j < 4 ; j++) 
            {
                if (guss[i][j] == s[j]){
                    b++;
                } else if (S.count(guss[i][j])){
                    c++;
                }
            }

            if (b != bulls[i]) flag = false;
            if (c != cows[i]) flag = false;
        }
        if (flag) ans.push_back(s);
    }
    
    if (ans.size() > 1) {
        cout << "Need more data" << endl;
    } else if (ans.size() == 1) {
        cout << ans[0] << endl;
    } else {
        cout << "Incorrect data" << endl;
    }
    
    return 0;
}