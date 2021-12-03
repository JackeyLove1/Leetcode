#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <bitset>
#include <cstring>
#include <queue>
#include <random>

using namespace std;


vector<int> destroyingHouses(vector<int> &houses, vector<int> &queries) {
    vector<int> res;
    map<int, bool> m;
    for (auto &house : houses) {
        // map保证了元素的顺序遍历
        m[house] = true;
    }
    const int INF = -1e9 - 2;
    for (auto &query : queries) {
        m.erase(query);
        int tmp = 0, st = INF;
        for (auto&[k, _] : m) {
            if (st == INF) {
                ++tmp;
                st = k;
            } else if (k == st + 1) {
                st = k;
            } else {
                ++tmp;
                st = k;
            }
        }
        res.push_back(tmp);
    }
    return res;
}

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) {
        cout << num << ' ';
    }
    cout << endl;
}

int main() {
    vector<int> nums = {1, 2, 3}, query = {2, 1};
    auto res = destroyingHouses(nums, query);
    print(res);
    vector<int> nums2 = {1, 2, 3}, query2 = {3, 1, 2};
    auto res2 = destroyingHouses(nums2, query2);
    print(res2);
}

