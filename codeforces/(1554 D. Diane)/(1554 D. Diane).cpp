#include <bits/stdc++.h>
using namespace std ;


int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        if(n == 1) {
            cout << "a" << endl;
            continue;
        }

        string s = "";
        for(int i = 0; i < (n-2)/2; i++){
            s += 'a';
        }
        string s_plus_a = s + "a";
        
          if(n%2){
            cout << s << "bc" << s_plus_a << endl;
        } else {
            cout << s << "b" << s_plus_a  << endl;
        }

      
    }


}