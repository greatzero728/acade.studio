#include <iostream>
#include <string>
using namespace std;

const int MOD = 1000000007;
const int ALPHABET_SIZE = 26;
const int MAX_LENGTH = 100;

int equivalenceClassSizes[MAX_LENGTH + 1][ALPHABET_SIZE * MAX_LENGTH + 1];

int calculateSum(const string& str) {
    int sum = 0;
    for (char c : str) {
        sum += c - 'a' + 1;
    }
    return sum;
}

void precomputeEquivalenceClassSizes() {
    for (int length = 1; length <= MAX_LENGTH; ++length) {
        for (int sum = length; sum <= ALPHABET_SIZE * length; ++sum) {
            if (length == 1) {
                equivalenceClassSizes[length][sum] = 1;
            } else {
                for (int i = 1; i <= ALPHABET_SIZE; ++i) {
                    if (sum - i >= 0) {
                        equivalenceClassSizes[length][sum] = (equivalenceClassSizes[length][sum] + equivalenceClassSizes[length - 1][sum - i]) % MOD;
                    }
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precomputeEquivalenceClassSizes();

    int t;
    cin >> t;
    while (t--) {
        string str;
        cin >> str;
        int sum = calculateSum(str);
        int result = equivalenceClassSizes[str.length()][sum] - 1;
        if (result < 0) {
            result += MOD;
        }
        cout << result << '\n';
    }

    return 0;
}