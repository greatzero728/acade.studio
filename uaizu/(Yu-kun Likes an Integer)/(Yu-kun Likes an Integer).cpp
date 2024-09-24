#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> combinations;

void gen(int idx, vector<int> comb) {
    if (idx == 0) {
        combinations.push_back(comb);
        return;
    }
    for (int i = 0; i < 10; i++) {
        comb.push_back(i);
        gen(idx - 1, comb);
        comb.pop_back();
    }
}
void acc() {
    int n, m;
    cin >> n >> m;
    vector<int> cost(10);
    for (int i = 0; i < 10; i++) {
        cin >> cost[i];
    }
    gen(n, {});
    std::sort(combinations.begin(), combinations.end());
    for (vector<int> comb: combinations) {
        int sum = 0;
        for (int digit: comb) {
            sum += cost[digit];
        }
        if (sum <= m) {
            for (int digit: comb) {
                cout << digit;
            }
            cout <<'\n';
            return;
        }
    }
    cout << "NA"<<'\n';
}

int main() {
    acc();
}