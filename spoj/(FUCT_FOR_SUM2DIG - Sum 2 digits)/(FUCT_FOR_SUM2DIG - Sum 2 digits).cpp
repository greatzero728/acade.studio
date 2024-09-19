#include <iostream>

int main() {
    int n;
    std::cin >> n;
    bool found = false;
    for (int x = 1; x <= 9; x++) {
        int y = n - x;
        if (y >= 0 && y <= 9) {
            std::cout << x * 10 + y << " = " << x << " + " << y << " = " << n << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "NO" << std::endl;
    }
    return 0;
}