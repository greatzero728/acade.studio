#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int R[3] = {0}, G[3] = {0}, B[3] = {0};

    for (int i = 0; i < n; i++) {
        switch (s[i]) {
            case 'R':
                R[i % 3]++;
                break;
            case 'G':
                G[i % 3]++;
                break;
            case 'B':
                B[i % 3]++;
                break;
        }
    }

    int minRecolors = n;
    std::string bestRecoloring;

    for (int r = 0; r < 3; r++) {
        for (int g = 0; g < 3; g++) {
            for (int b = 0; b < 3; b++) {
                if (r == g || r == b || g == b) continue;

                int recolors = 0;
                for (int i = 0; i < n; i++) {
                    int color = (i % 3 == r ? 'R' : (i % 3 == g ? 'G' : 'B'));
                    if (s[i] != color) recolors++;
                }

                if (recolors < minRecolors) {
                    minRecolors = recolors;
                    bestRecoloring = "";
                    for (int i = 0; i < n; i++) {
                        int color = (i % 3 == r ? 'R' : (i % 3 == g ? 'G' : 'B'));
                        bestRecoloring += color;
                    }
                }
            }
        }
    }

    std::cout << minRecolors << std::endl;
    std::cout << bestRecoloring << std::endl;

    return 0;
}
