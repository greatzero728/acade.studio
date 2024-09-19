#include <bits/stdc++.h>

using namespace std;

int main() {
    int cases = 1;
    while (1) {
        int n, ma, mb;
        cin >> n >> ma >> mb;
        if (n == 0 && ma == 0 && mb == 0) {
            return 0;
        }
        int la, lb, da, db;
        cin >> la >> lb >> da >> db;
        int matrixA[8][8] = {};
        for (int i = 0; i < ma; i++) {
            int u, v;
            cin >> u >> v;
            matrixA[u][v] = 1;
            matrixA[v][u] = 1;
        }
        int matrixB[8][8] = {};
        for (int i = 0; i < mb; i++) {
            int u, v;
            cin >> u >> v;
            matrixB[u][v] = 1;
            matrixB[v][u] = 1;
        }
        vector<int> first(n);
        std::iota(first.begin(), first.end(), 0);
        int answer = 1e9;
        do {
            int cost = 0;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    int x = first[i], y = first[j];
                    //if edge between x,y in first graph and i,j in second are found in both
                    if (matrixA[x][y] == 1 && matrixB[i][j] == 1) {
                        continue;
                    }
                    //if edge between x,y in first graph and i,j in second are not found in both
                    if (matrixA[x][y] == 0 && matrixB[i][j] == 0) {
                        continue;
                    }
                    //if edge between x,y in first graph and i,j in second are found in first graph but not in second
                    //so we will check what is the best , add it in second graph with cost lb
                    //or delete it from first graph with cost da
                    if (matrixA[x][y] == 1 && matrixB[i][j] == 0) {
                        cost += min(lb, da);
                        continue;
                    }
                    //if edge between x,y in first graph and i,j in second are found in second graph but not in first
                    //so we will check what is the best , add it in first graph with cost la
                    //or delete it from second graph with cost db
                    if (matrixA[x][y] == 0 && matrixB[i][j] == 1) {
                        cost += min(la, db);
                        continue;
                    }
                }
            }
            answer = min(answer, cost);
        } while (next_permutation(first.begin(), first.end()));
        if (n == 1) {
            answer = 0;
        }
        cout << "Case #" << cases++ << ": " << answer << '\n';
    }
}