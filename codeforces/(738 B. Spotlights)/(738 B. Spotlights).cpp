#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> grid(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> grid[i][j];
        }
    }

    int goodPositions = 0;

    std::vector<std::vector<int>> left(n, std::vector<int>(m));
    std::vector<std::vector<int>> right(n, std::vector<int>(m));
    std::vector<std::vector<int>> up(n, std::vector<int>(m));
    std::vector<std::vector<int>> down(n, std::vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                left[i][j] = right[i][j] = up[i][j] = down[i][j] = 1;
                for (int k = j - 1; k >= 0; k--) {
                    if (left[i][k] == 0) {
                        left[i][k] = 1;
                    } else {
                        break;
                    }
                }
                for (int k = j + 1; k < m; k++) {
                    if (right[i][k] == 0) {
                        right[i][k] = 1;
                    } else {
                        break;
                    }
                }
                for (int k = i - 1; k >= 0; k--) {
                    if (up[k][j] == 0) {
                        up[k][j] = 1;
                    } else {
                        break;
                    }
                }
                for (int k = i + 1; k < n; k++) {
                    if (down[k][j] == 0) {
                        down[k][j] = 1;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                goodPositions += left[i][j] + right[i][j] + up[i][j] + down[i][j];
            }
        }
    }

    std::cout << goodPositions << std::endl;

    return 0;
}