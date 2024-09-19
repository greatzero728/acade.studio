#include <bits/stdc++.h>

using namespace std;

vector<int> BFS(int &root, int &n, vector<vector<int>> &graph) {
    vector<int> Distance(n + 5, 1e9);
    queue<int> q;
    q.push(root);
    Distance[root] = 0;
    while (q.size()) {
        int node = q.front();
        q.pop();
        for (auto i: graph[node]) {
            if (Distance[node] + 1 < Distance[i]) {
                Distance[i] = Distance[node] + 1;
                q.push(i);
            }
        }
    }
    return Distance;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(0);
    int tests;
    cin >> tests;
    while (tests--) {
        int n, a, b, da, db;
        cin >> n >> a >> b >> da >> db;
        vector<vector<int>> graph(n + 5);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<int> DistanceFromA = BFS(a, n, graph);
        if (DistanceFromA[b] <= da) {
            cout << "Alice" << endl;
            continue;
        }
        int NewNode = 0;
        int MaxLenght = 0;
        for (int i = 1; i <= n; i++) {
            if (DistanceFromA[i] > MaxLenght) {
                MaxLenght = DistanceFromA[i];
                NewNode = i;
            }
        }
        //now get the maximum lenght from new node
        DistanceFromA = BFS(NewNode, n, graph);
        MaxLenght = 0;
        for (int i = 1; i <= n; i++) {
            if (DistanceFromA[i] > MaxLenght) {
                MaxLenght = DistanceFromA[i];
            }
        }
        if (da * 2 >= MaxLenght || da * 2 >= db) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
}