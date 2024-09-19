#include <bits/stdc++.h>
using namespace std;

bool attempt_match(int rootA, int rootB, vector<vector<int>>& netA, vector<vector<int>>& netB, vector<int>& assigned) {
    int n = netA.size();
    fill(assigned.begin(), assigned.end(), -1);
    assigned[rootA] = rootB;
    
    vector<int> free_nodes;
    vector<int> blocked_in_B(n, -1);
    blocked_in_B[rootB] = rootB;

    for(int i = 0; i < n; i++) 
        if(assigned[i] == -1) free_nodes.push_back(i);
    
    vector<bool> visited_A(n, false);
    queue<int> q;
    q.push(rootA);

    while(!q.empty()) {
        int nodeA = q.front(), nodeB = assigned[nodeA];
        
        for(int adjA : netA[nodeA])
            visited_A[adjA] = true;

        for(int adjB : netB[nodeB]) {
            if(blocked_in_B[adjB] == -1) {
                blocked_in_B[adjB] = nodeA;
                
                int free_match = -1;
                for(int i = 0; i < (int)netA[nodeA].size() + 3; i++) {
                    int random_index = rand() % free_nodes.size();
                    if(!visited_A[free_nodes[random_index]]) {
                        free_match = free_nodes[random_index];
                        swap(free_nodes[random_index], free_nodes.back());
                        free_nodes.pop_back();
                        break;
                    }
                }

                if(free_match == -1) return false;

                assigned[free_match] = adjB;
                q.push(free_match);
            }
        }

        for(int adjA : netA[nodeA])
            visited_A[adjA] = false;

        q.pop();
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int N;
    cin >> N;

    vector<vector<int>> network[2];
    vector<int> degree[2], max_degree_root(2);

    for(int i = 0; i < 2; i++) {
        network[i].resize(N);
        degree[i].resize(N, 0);
        for(int j = 0; j < N-1; j++) {
            int u, v;
            cin >> u >> v;
            if(i == 1) {
                u -= N;
                v -= N;
            }
            network[i][--u].push_back(--v);
            network[i][v].push_back(u);
            degree[i][u]++;
            degree[i][v]++;
        }

        max_degree_root[i] = 0;
        for(int j = 0; j < N; j++) {
            if(degree[i][j] > degree[i][max_degree_root[i]]) 
                max_degree_root[i] = j;
        }
    }

    int trials = 100;
    srand(23479 + N);

    for(int trial = 0; trial < trials; trial++) {
        int network_choice = rand() % 2;
        vector<int> available_roots;

        for(int i = 0; i < N; i++) {
            if(N - 1 - degree[1 - network_choice][i] >= degree[network_choice][max_degree_root[network_choice]])
                available_roots.push_back(i);
        }
        
        if(available_roots.empty()) continue;

        int selected_root = available_roots[rand() % available_roots.size()];
        vector<int> final_mapping[2];

        for(int i = 0; i < 2; i++)
            final_mapping[i].resize(N);

        bool success = attempt_match(max_degree_root[network_choice], selected_root, network[network_choice], network[1 - network_choice], final_mapping[network_choice]);

        if(success) {
            cout << "Yes\n";
            for(int i = 0; i < N; i++) 
                final_mapping[1 - network_choice][final_mapping[network_choice][i]] = i;
            
            for(int i = 0; i < N; i++) 
                cout << N + 1 + final_mapping[0][i] << (i == N - 1 ? "\n" : " ");
            
            return 0;
        }
    }

    cout << "No\n";
}
