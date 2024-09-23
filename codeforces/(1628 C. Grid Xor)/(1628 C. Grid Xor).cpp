#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1005;
bool isActivated[MAX_N][MAX_N];
int gridSize;
int neighborXorSums[MAX_N][MAX_N];

const int deltaX[] = {-1, 1, 0, 0};
const int deltaY[] = {0, 0, -1, 1};
void toggleNeighbors(int row, int col) {
    for (int direction = 0; direction < 4; direction++) {
        int neighborRow = row + deltaX[direction];
        int neighborCol = col + deltaY[direction];
        if (neighborRow >= 1 && neighborRow <= gridSize && neighborCol >= 1 && neighborCol <= gridSize) {
            isActivated[neighborRow][neighborCol] ^= 1;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    while (testCases--) {
        cin >> gridSize;
        for (int row = 1; row <= gridSize; row++) {
            for (int col = 1; col <= gridSize; col++) {
                cin >> neighborXorSums[row][col];
                isActivated[row][col] = false;
            }
        }

        int totalXor = 0;
        for (int row = 2; row <= gridSize; row++) {
            for (int col = 1; col <= gridSize; col++) {
                if (!isActivated[row - 1][col]) {
                    toggleNeighbors(row, col);
                    totalXor ^= neighborXorSums[row][col];
                }
            }
        }
        cout << totalXor << '\n';
    }
    return 0;
}