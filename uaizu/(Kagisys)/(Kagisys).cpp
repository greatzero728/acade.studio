#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> registered_ids(n);
    for (int i = 0; i < n; i++) {
        cin >> registered_ids[i];
    }
    int m;
    cin >> m;
    vector<string> ic_card_ids(m);
    for (int i = 0; i < m; i++) {
        cin >> ic_card_ids[i];
    }
    unordered_set<string> registered_ids_set(registered_ids.begin(), registered_ids.end());
    bool is_locked = true;
    for (const string& id : ic_card_ids) {
        if (registered_ids_set.find(id) != registered_ids_set.end()) {
            if (is_locked) {
                cout << "Opened by " << id << endl;
                is_locked = false;
            } else {
                cout << "Closed by " << id << endl;
                is_locked = true;
            }
        } else {
            cout << "Unknown " << id << endl;
        }
    }
    return 0;
}