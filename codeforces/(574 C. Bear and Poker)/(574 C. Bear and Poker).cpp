#include <iostream>
#include <vector>

int remove_2_and_3(int x) {
    while (x % 2 == 0) x /= 2;
    while (x % 3 == 0) x /= 3;
    return x;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> k(n);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        k[i] = remove_2_and_3(x);
    }
    for (int i = 1; i < n; i++) {
        if (k[i] != k[0]) {
            std::cout << "No";
            return 0;
        }
    }
    std::cout << "Yes";
    return 0;
}