#include <iostream>
#include <cstdint>

int main() {
    uint64_t A, B;
    std::cin >> A >> B;

    if (A < B || (A - B) % 2 != 0) {
        std::cout << "-1\n";
        return 0;
    }

    uint64_t X = (A - B) / 2;
    uint64_t Y = A - X;

    std::cout << X << " " << Y << "\n";

    return 0;
}