#include <bits/stdc++.h>
using namespace std;

struct P{
    int x, y;
};
struct Lines{
    int first,second;
};

vector<string> grid(5);
vector<string> out(5);
vector<P> points(12);
vector<Lines> lines(12);

vector<bool> flag(12, false);
vector<int> sum(6, 26);
bool done = false;

int find(int i, int j) {
    for (int k = 0; k < 12; k++) {
        if (points[k].x == i && points[k].y == j) return k;
    }
    return -1;
}


void go(int id) {

    
    if (id == 12) {
        for (string line : out){
            cout << line << '\n';
        }
        done = true;
        return;
    }

    if (grid[points[id].x][points[id].y] != 'x') {
        go(id + 1);
        return;
    }

    for (int i = 0; i < 12; i++) {
        if (!flag[i]) {
            int a = lines[id].first;
            int b = lines[id].second;

            if (sum[a] < i + 1 || sum[b] < i + 1) return;

            sum[a] -= i + 1;
            sum[b] -= i + 1;
            flag[i] = true;
            char tmp = out[points[id].x][points[id].y];
            out[points[id].x][points[id].y] = 'A' + i;

            go(id + 1);

            if (done) return;

            out[points[id].x][points[id].y] = tmp;
            flag[i] = false;
            sum[a] += i + 1;
            sum[b] += i + 1;
        }
    }
    
}


int main() {


    for (int i = 0; i < 5; i++) {
        cin >> grid[i];
    }

    points = {{0, 4}, {1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 2}, {2, 6}, {3, 1}, {3, 3}, {3, 5}, {3, 7}, {4, 4}};
    lines = {{0, 1}, {2, 3}, {0, 2}, {1, 2}, {2, 4}, {0, 3}, {1, 4}, {0, 5}, {3, 5}, {4, 5}, {1, 5}, {3, 4}};

    out = grid;
     
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] != '.' && grid[i][j] != 'x') {
                int k = find(i, j);
                int a = lines[k].first;
                int b = lines[k].second;
                sum[a] -= (grid[i][j] - 'A' + 1);
                sum[b] -= (grid[i][j] - 'A' + 1);
                flag[grid[i][j] - 'A'] = true;
            }
        }
    }
    
    go(0);
    
}