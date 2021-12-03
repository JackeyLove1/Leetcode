#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <array>
#include <memory>
#include <regex>
#include <thread>
#include <atomic>
#include <future>
#include <deque>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    cout << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "ending ... " << endl;
}


vector<int> restoreArray(vector<vector<int>> &adjacentPairs) {
    vector<int> res;
    if (adjacentPairs.empty()) return res;
    unordered_map<int, vector<int>> um;
    unordered_set<int> visited;
    for (auto &ps : adjacentPairs) {
        um[ps[0]].push_back(ps[1]), um[ps[1]].push_back(ps[0]);
    }
    queue<int> q;
    for (auto&[k, v] : um) {
        if (v.size() == 1) {
            q.push(k);
            break;
        }
        if (v.size() > 2) return res;
        // cout << k << " vec: ";
        // print(v);
    }
    if (q.empty()) q.push(adjacentPairs[0][0]);
    while (!q.empty()) {
        // for_each(q.begin(), q.end(), [](int x) {cout << x <<" ";});
        // cout << endl;
        auto t = q.front();
        q.pop();
        res.push_back(t);
        visited.insert(t);
        auto vec = um[t];
        // cout << t << " vec: ";
        // print(vec);
        for (auto &num : vec) {
            if (!visited.count(num)) {
                q.push(num);
                //cout << "add: " << num << " ";
            }
        }
        // cout << endl;
    }
    return res;
}

int main() {
    vector<vector<int>> nums = {{2, 1},
                                {3, 4},
                                {3, 2}};
    auto res = restoreArray(nums);
    print(res);
}