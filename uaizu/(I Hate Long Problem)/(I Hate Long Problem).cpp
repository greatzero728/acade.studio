#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, X;
    cin >> N >> X;
    vector<int> M(N);
    for (int i = 0; i < N; i++) {
        cin >> M[i];
    }
    int ignored = 0;
    for (int i = 0; i < N; i++) {
        if (M[i] >= X) {
            ignored++;
        }
    }
    cout << ignored << endl;
    return 0;
}