#include<bits/stdc++.h>
using namespace std;
bool hasBridge = false;
void bridgeUtil(int node, int parent,vector<vector<int>> &adjacency_list,vector<bool>& visited, vector<int>& discovery_time, vector<int>& lowest_discovery_time, vector<pair<int,int>> &edges_orientation){
    static int time = 0;
    visited[node] = true;
    discovery_time[node] = lowest_discovery_time[node] = time++;
    for (auto child : adjacency_list[node]){
        if(child == parent) continue;
        if(visited[child]){
            lowest_discovery_time[node]  = min(lowest_discovery_time[node], discovery_time[child]);
            if(discovery_time[node] > discovery_time[child]){
                edges_orientation.push_back({node,child});
            }
        }else{
            bridgeUtil(child,node, adjacency_list,visited,discovery_time,lowest_discovery_time,edges_orientation);
            if (lowest_discovery_time[child] > discovery_time[node]){
                hasBridge = true;
                return;
            }
            edges_orientation.push_back({node,child});
            lowest_discovery_time[node]  = min(lowest_discovery_time[node], lowest_discovery_time[child]);
        }
    }
}
int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adjacency_list(n+1);
    for (int i = 0;i < m;i++){
        int a,b ; cin >> a >> b;
        adjacency_list[a].push_back(b);
        adjacency_list[b].push_back(a);
    }
    vector<bool> visited(n+1);
    vector<int> discovery_time(n+1),lowest_discovery_time(n+1);
    vector<pair<int,int>> edges_orientation;
    bridgeUtil(1,-1,adjacency_list,visited,discovery_time,lowest_discovery_time,edges_orientation);
    if(hasBridge){
        cout << 0 << endl;
    }else{
        for (auto edge : edges_orientation){
            cout << edge.first << ' ' << edge.second << endl;
        }
    }
    return 0;
}