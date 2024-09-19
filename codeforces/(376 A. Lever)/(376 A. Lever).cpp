#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    long long left_weight = 0;
    long long right_weight = 0;
    int pivot = -1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '^') {
            pivot = i;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '1' && s[i] <= '9') {
            if (i < pivot) {
                left_weight += (pivot - i) * (s[i] - '0');
            } else if (i > pivot) {
                right_weight += (i - pivot) * (s[i] - '0');
            }
        }
    }
    if (left_weight > right_weight) {
        cout << "left" << endl;
    } else if (left_weight < right_weight) {
        cout << "right" << endl;
    } else {
        cout << "balance" << endl;
    }
    return 0;
}