#include <bits/stdc++.h>

using namespace std;

struct Comparator {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second < b.second;
    }
};

int main(){
    int q;
    cin >> q;
    int id = 1;
    set<pair<int,int>,Comparator> amount;
    map<int,int> idToAmount;
    set<int> order;
    for (int i = 0;i < q;++i){
        int t;
        cin >> t;
        if (t == 1){
            int m;
            cin >> m;
            order.insert(id);
            amount.insert({m,id});
            idToAmount[id] = m;
            id++;
        }
        else if(t == 2){
            int x = *order.begin();
            cout << x << " ";
            order.erase(order.begin());
            amount.erase(amount.find({idToAmount[x],x}));
        }
        else{
            pair<int,int> x = *amount.begin();
            cout << x.second << " ";
            amount.erase(amount.begin());
            order.erase(order.find(x.second));
        }
    }


    return 0;
}