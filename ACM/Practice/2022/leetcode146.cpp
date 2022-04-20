#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <list>
#include <numeric>
#include <cstring>
#include <queue>
#include <string>
#include <climits>

using namespace std;

template<typename T>
static inline void print(vector<T> &vec) {
    for_each(vec.begin(), vec.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

static inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

inline int cnt(int x) {
    return __builtin_popcount(x);
}

constexpr int N = 2200, M = 550;
constexpr int INF = 0x3f3f3f3f;
using ll = long long;


class LRUCache {
private:
    using iter = list<int>::iterator;
    unordered_map<int, iter> lru_map;
    list<int> lru_list;
    int capacity_;
public:
    LRUCache(int capacity) : capacity_(capacity) {
        lru_map.reserve(capacity_);
    }

    int get(int key) {
        if (lru_map.count(key)) {
            auto it = lru_map[key];
            int value = *it;
            lru_list.erase(it);
            lru_list.emplace_front(value);
            return value;
        }
        return -1;
    }

    void put(int key, int value) {
        // contains the key
        if (lru_map.count(key)) {
            auto it = lru_map[key];
            lru_list.erase(it);
            lru_list.emplace_front(value);
            lru_map[key] = lru_list.begin();
            return;
        }
        // delete the old key
        if (lru_list.size() >= capacity_) {
            // delete old iterator
            auto old_iter = lru_map[lru_list.back()];
            lru_map.erase(*old_iter);
            lru_list.erase(old_iter);
        }
        // insert the new key
        lru_list.emplace_front(key);
        lru_map[key] = lru_list.begin();
    }

    void print() {
        for (const auto &it : lru_list) {
            cout << it << " ";
        }
        cout << endl;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    auto lru = LRUCache(2);
    lru.put(1, 1);
    lru.print();  // 1
    lru.put(2, 2);
    lru.print(); // 2, 1
    lru.get(1);
    lru.print(); // 1, 2
    lru.put(3, 3);
    lru.print(); // 3,1
    cout << lru.get(2) << endl; // -1
    lru.put(4,4); // 4,3
    lru.print();
    cout << lru.get(1) << endl; // -1
    cout << lru.get(3) << endl; // 3
    cout << lru.get(4) << endl; // 4
}