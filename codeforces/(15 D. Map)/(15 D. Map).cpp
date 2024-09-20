#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Rectangle {
    ll removal;
    int row;
    int col;
};

bool cmp(const Rectangle &a, const Rectangle &b) {
    if(a.removal != b.removal)
        return a.removal < b.removal;
    if(a.row != b.row)
        return a.row < b.row;
    return a.col < b.col;
}

vector<int> sliding_min(const vector<int>& arr, int window_size) {
    deque<int> dq;
    vector<int> min_vals;
    for(int i = 0; i < arr.size(); ++i){
        while(!dq.empty() && arr[i] <= arr[dq.back()]){
            dq.pop_back();
        }
        dq.push_back(i);
        while(!dq.empty() && dq.front() <= i - window_size){
            dq.pop_front();
        }
        if(i >= window_size -1){
            min_vals.push_back(arr[dq.front()]);
        }
    }
    return min_vals;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<vector<int>> A(n, vector<int>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> A[i][j];
        }
    }

    vector<vector<ll>> prefix_sum(n+1, vector<ll>(m+1, 0));
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            prefix_sum[i][j] = A[i-1][j-1] + prefix_sum[i-1][j] + prefix_sum[i][j-1] - prefix_sum[i-1][j-1];
        }
    }

    vector<vector<int>> row_min(n, vector<int>());
    for(int i=0;i<n;i++) {
        row_min[i] = sliding_min(A[i], b);
    }

    int rows = n - a +1;
    int cols = m - b +1;
    vector<vector<int>> min_grid(rows, vector<int>(cols, 0));

    for(int j=0; j < cols; j++){
        vector<int> column;
        for(int i=0;i<n;i++) {
            column.push_back(row_min[i][j]);
        }
        vector<int> col_min = sliding_min(column, a);
        for(int i=0; i < rows; i++) {
            min_grid[i][j] = col_min[i];
        }
    }

    vector<Rectangle> rectangles;
    rectangles.reserve(static_cast<size_t>(rows) * cols);
    for(int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            ll sum_rect = prefix_sum[i+a][j+b] - prefix_sum[i][j+b] - prefix_sum[i+a][j] + prefix_sum[i][j];
            int min_h = min_grid[i][j];
            ll removal = sum_rect - (1LL * min_h * a * b);
            rectangles.push_back(Rectangle{removal, i+1, j+1});
        }
    }

    sort(rectangles.begin(), rectangles.end(), cmp);

    int num_words = (m +63)/64;
    vector< vector<ull> > occupied(n, vector<ull>(num_words, 0));

    vector<tuple<int, int, ll>> result;
    result.reserve(rectangles.size());

    vector< vector<pair<int, ull>> > masks(cols, vector<pair<int, ull>>());
    for(int j=0; j < cols; j++) {
        int word_start = j / 64;
        int bit_start = j % 64;
        int word_end = (j + b -1) /64;
        int bit_end = (j + b -1) %64;
        if(word_start == word_end){
            ull mask = (bit_end +1 == 64) ? ~0ULL : ((1ULL << (bit_end +1)) -1);
            mask &= (~0ULL << bit_start);
            masks[j].emplace_back(word_start, mask);
        }
        else{
            ull mask_start = ~0ULL << bit_start;
            masks[j].emplace_back(word_start, mask_start);
            for(int w = word_start +1; w < word_end; w++) {
                masks[j].emplace_back(w, ~0ULL);
            }
            ull mask_end;
            if(bit_end +1 == 64){
                mask_end = ~0ULL;
            }
            else{
                mask_end = (1ULL << (bit_end +1)) -1;
            }
            masks[j].emplace_back(word_end, mask_end);
        }
    }

    for(auto &rect : rectangles){
        int i = rect.row -1;
        int j = rect.col -1;
        if(j + b > m || i +a > n){
            continue;
        }
        bool conflict = false;
        for(int x =i; x < i +a; x++) {
            for(auto &[word, mask] : masks[j]){
                if(occupied[x][word] & mask){
                    conflict = true;
                    break;
                }
            }
            if(conflict) break;
        }
        if(!conflict){
            result.emplace_back(make_tuple(rect.row, rect.col, rect.removal));
            for(int x =i; x < i +a; x++) {
                for(auto &[word, mask] : masks[j]){
                    occupied[x][word] |= mask;
                }
            }
        }
    }

    cout << result.size() << "\n";
    for(auto &[r, c, rem] : result){
        cout << r << " " << c << " " << rem << "\n";
    }

    return 0;
}