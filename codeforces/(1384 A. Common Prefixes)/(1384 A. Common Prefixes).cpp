#include <bits/stdc++.h>

using namespace std;

const int NN = 121;

int a[NN];

int main() {
    int T, N;
    cin >> T;

    while (T--) {
        cin >> N;
        for(int i = 0; i < N; i++) cin>>a[i];
        
        string S(*max_element(a, a + N), 'a');
        
        cout<<S<<endl;
        for(int i = 0; i < N; i++) {
            S[a[i]] = (S[a[i]] == 'a') ? 'b' : 'a';
            cout << S << endl;
        }
    }

    return 0;
}