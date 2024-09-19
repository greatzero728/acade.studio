#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

class SegmentTree {
public:
    int size;
    bool is_mod;
    vector<long long> values;
    
    SegmentTree(int n, bool is_mod_ = false) {
        is_mod = is_mod_;
        size = 1;
        while (size < n) {
            size *= 2;
        }
        values.resize(2 * size);
    }
    
    void update(int pos, long long value) {
        int curr = pos + size;
        values[curr] = value;
        if (is_mod) values[curr] %= mod;
        while (curr > 1) {
            curr /= 2;
            values[curr] = values[2 * curr] + values[2 * curr + 1];
            if (is_mod) values[curr] %= mod;
        }
    }
    
    long long get_sum(int l, int r) {
        long long result = 0;
        l += size;
        r += size;
        while (l <= r) {
            if (l % 2 == 1) {
                result += values[l];
                if (is_mod) result %= mod;
                l += 1;
            }
            if (r % 2 == 0) {
                result += values[r];
                if (is_mod) result %= mod;
                r -= 1;
            }
            l /= 2;
            r /= 2;
        }
        return result;
    }
    
    int find_target_sum(long long target_sum) {
        int v = 1;
        long long min_sum = 0;
        while(true) {
            if (v >= size) return v - size;
            
            if (min_sum + values[2*v] >= target_sum) {
                v = 2*v;
            } else {
                min_sum += values[2*v];
                v = 2*v + 1;
            }
        }
    }
};


int main() {
    int n, q;
    cin >> n >> q;
    vector<int> pos(n);
    vector<int> weights(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> pos[i];
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }
    
    SegmentTree tree(n);
    SegmentTree tree_b(n, true);
    SegmentTree tree_e(n, true);
    for (int i = 0; i < n; ++i) {
        tree.update(i, weights[i]);
        tree_b.update(i, weights[i] * 1ll * (pos[i] - i - 1));
        tree_e.update(i, weights[i] * 1ll * (1000000000 - pos[i] - n + i + 1));
    }
    
    for (int ii = 0; ii < q; ++ii) {
        int x, y;
        cin >> x >> y;
        if (x < 0) {
            int id = -x - 1;
            int nw = y;
            tree.update(id, nw);
            tree_b.update(id, nw * 1ll * (pos[id] - id - 1));
            tree_e.update(id, nw * 1ll * (1000000000 - pos[id] - n + id + 1));
        } else {
            int first = x-1;
            int last = y-1;
            
            long long sum = tree.get_sum(first, last);
            long long start_sum = tree.get_sum(0, first-1);
            long long target_sum = start_sum + (sum+1) / 2;
            int m = tree.find_target_sum(target_sum);
            
            long long suml = tree_e.get_sum(first, m);
            long long sum_w_l = tree.get_sum(first, m) % mod;
            suml += mod - ((sum_w_l * (1000000000 - (n - m - 1) - pos[m])) % mod);
            long long sumr = tree_b.get_sum(m+1, last);
            long long sum_w_r = tree.get_sum(m+1, last) % mod;
            if (m+1 < n)
                sumr += mod - ((sum_w_r * (pos[m]+1 - (m+1) - 1)) % mod);
            
            cout << ((suml + sumr) % mod) << '\n';
        }
    }
    
    return 0;
}