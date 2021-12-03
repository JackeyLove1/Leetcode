// Author: Jacky
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <queue>
#include <tuple>
#include <deque>

using namespace std;
using PII = pair<int, int>;
using ll = long long;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

class StockPrice {
private:
    using PII = pair<int, int>;
    map<int, int> time;
    map<int, unordered_set<int>> value;
public:
    StockPrice() {

    }

    void update(int timestamp, int price) {
        if (time.count(timestamp)) {
            auto oldValue = time[timestamp];
            value[oldValue].erase(timestamp);
            if (value[oldValue].empty()) {
                value.erase(oldValue);
            }
        }
        time[timestamp] = price;
        value[price].insert(timestamp);
    }

    int current() {
        auto it = time.end();
        return (--it)->second;
    }

    int maximum() {
        auto it = value.end();
        return (--it)->first;
    }

    int minimum() {
        return value.begin()->first;
    }

    void print() const {
        cout << "time" << endl;
        for (auto&[k, v] : time) {
            cout << "k: " << k << " v: " << v << endl;
        }
        cout << "value" << endl;
        for (auto&[k, v] : value) {
            cout << "k: " << k << " time: ";
            for (auto &t : v) {
                cout << t << " ";
            }
            cout << endl;
        }
        cout << "using iter: " << endl;
        for (auto it = time.begin(); it != time.end(); ++it) {
            cout << it->first << " " << it->second << endl;
        }
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */

int main() {
    auto s = StockPrice();
    s.update(1, 10);
    // s.print();
    s.update(2, 5);
    s.print();
    cout << s.current() << " res: 5" << endl;
    cout << s.maximum() << " res: 10" << endl;

}