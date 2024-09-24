#include <iostream>
#include <vector>
#include <sstream>

int main() {
    std::string line;
    int K;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        iss >> K;
        if (K == 0) break;

        std::vector<int> c(K * (K - 1) / 2);
        std::getline(std::cin, line);
        std::istringstream iss2(line);
        for (int i = 0; i < c.size(); ++i) {
            iss2 >> c[i];
        }

        int sum = 0;
        for (int i = 0; i < c.size(); ++i) {
            sum += c[i];
        }
        int total_sales_quantity = sum / (K - 1);
        std::cout << total_sales_quantity << std::endl;
    }
    return 0;
}