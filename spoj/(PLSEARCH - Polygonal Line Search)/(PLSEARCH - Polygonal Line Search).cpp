#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> getVectors(vector<pair<int, int>>& line) {
    vector<pair<int, int>> vectors;
    for (size_t i = 1; i < line.size(); ++i) {
        int dx = line[i].first - line[i - 1].first;
        int dy = line[i].second - line[i - 1].second;
        vectors.push_back({dx, dy});
    }
    return vectors;
}

pair<int, int> rotate90(pair<int, int> vec) {
    return {vec.second, -vec.first};
}

vector<vector<pair<int, int>>> generateAllRotations(vector<pair<int, int>>& vectors) {
    vector<vector<pair<int, int>>> rotations(4);
    rotations[0] = vectors;
    for (int i = 1; i < 4; ++i) {
        for (auto& vec : rotations[i - 1]) {
            rotations[i].push_back(rotate90(vec));
        }
    }
    return rotations;
}

bool areEqual(vector<pair<int, int>>& a, vector<pair<int, int>>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool matchesTemplate(vector<pair<int, int>>& line, vector<pair<int, int>>& templateVectors) {
    auto templateRotations = generateAllRotations(templateVectors);
    vector<pair<int, int>> reversedTemplate(templateVectors.rbegin(), templateVectors.rend());
    auto reversedTemplateRotations = generateAllRotations(reversedTemplate);
    auto lineVectors = getVectors(line);
    for (auto& rotation : templateRotations) {
        if (areEqual(lineVectors, rotation)) return true;
    }
    for (auto& rotation : reversedTemplateRotations) {
        if (areEqual(lineVectors, rotation)) return true;
    }
    return false;
}

int main() {
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break; 
        vector<vector<pair<int, int>>> lines(n + 1);
        int m;
        for (int i = 0; i <= n; ++i) {
            cin >> m;
            vector<pair<int, int>> line(m);
            for (int j = 0; j < m; ++j) {
                cin >> line[j].first >> line[j].second;
            }
            lines[i] = line;
        }
        vector<pair<int, int>> templateVectors = getVectors(lines[0]);
        vector<int> matchingLines;
        for (int i = 1; i <= n; ++i) {
            if (matchesTemplate(lines[i], templateVectors)) {
                matchingLines.push_back(i);
            }
        }
        for (int idx : matchingLines) {
            cout << idx << endl;
        }
        cout << "+++++" << endl;
    }
}