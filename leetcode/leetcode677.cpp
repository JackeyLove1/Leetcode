#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>

using namespace std;

class MapSum {
public:
    /** Initialize your data structure here. */
    unordered_map<string, int> hash;

    MapSum() {

    }

    void insert(string key, int val) {
        hash[key] = val;
    }

    int sum(string prefix) {
        int res = 0;
        for (auto it = hash.begin(); it != hash.end(); it++) {
            if (it->first.find(prefix) == 0)
                res += it->second;
        }
        return res;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */