#include <iostream>

int main() {
    int64_t n, m;
    std::cin >> n >> m;

    if (n >= 27) {
        std::cout << m << std::endl;
        return 0;
    }

    int64_t mask = (1LL << n) - 1;
    int64_t result = m & mask;
    std::cout << result << std::endl;

    return 0;
}