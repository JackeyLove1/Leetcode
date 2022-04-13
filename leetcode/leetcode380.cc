#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <cmath>

using namespace std;

class RandomizedSet {
private:
    unordered_set<int> us;
    vector<int> vec;
public:
    RandomizedSet() {
        vec.reserve(100);
    }

    bool insert(int val) {
        if (us.count(val)) {
            return false;
        }
        us.insert(val);
        return true;
    }

    bool remove(int val) {
        if (us.count(val)) {
            us.erase(val);
            return true;
        }
        return false;
    }

    int getRandom() {
        int sz = us.size();
        int place = rand() % sz;
        vec.assign(us.begin(), us.end());
        return vec[place];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */