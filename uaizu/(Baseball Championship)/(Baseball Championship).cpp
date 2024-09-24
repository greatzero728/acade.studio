#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Team {
    std::string name;
    int wins;
    int losses;
};

int main() {
    int n;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        std::vector<Team> teams;

        for (int i = 0; i < n; i++) {
            Team team;
            std::cin >> team.name;
            team.wins = 0;
            team.losses = 0;

            for (int j = 0; j < n - 1; j++) {
                int result;
                std::cin >> result;
                if (result == 0) {
                    team.wins++;
                } else if (result == 1) {
                    team.losses++;
                }
            }

            teams.push_back(team);
        }

        std::sort(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
            if (a.wins != b.wins) {
                return a.wins > b.wins;
            } else {
                return a.losses < b.losses;
            }
        });

        for (const auto& team : teams) {
            std::cout << team.name << std::endl;
        }
    }

    return 0;
}