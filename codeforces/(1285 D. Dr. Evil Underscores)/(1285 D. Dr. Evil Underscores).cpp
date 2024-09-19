#include <bits/stdc++.h>
using namespace std;

// Function to solve the problem recursively by dividing the numbers based on bits
int find_min_xor(vector<int> &nums, int bit) {
    if (nums.empty() || bit < 0) return 0;

    // Divide the numbers into two groups: those with the current bit set and those without
    vector<int> group_with_bit, group_without_bit;
    for (int num : nums) {
        if (num & (1 << bit)) {
            group_with_bit.push_back(num);
        } else {
            group_without_bit.push_back(num);
        }
    }

    // If one group is empty, we can safely ignore this bit and continue with the non-empty group
    if (group_with_bit.empty()) return find_min_xor(group_without_bit, bit - 1);
    if (group_without_bit.empty()) return find_min_xor(group_with_bit, bit - 1);

    // If both groups are non-empty, solve recursively for both groups and add the current bit's influence
    return min(find_min_xor(group_with_bit, bit - 1), find_min_xor(group_without_bit, bit - 1)) + (1 << bit);
}

int main() {
    // Fast input-output optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int &num : a) {
        cin >> num;
    }

    // Start solving from the 29th bit (since a_i <= 2^30 - 1)
    cout << find_min_xor(a, 29) << "\n";

    return 0;
}