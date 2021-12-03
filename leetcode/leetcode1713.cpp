#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


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


int minOperations(vector<int> &target, vector<int> &arr) {
    int n = target.size();
    unordered_map<int, int> pos;
    for (int i = 0; i < n; ++i) {
        pos[target[i]] = i;
    }
    vector<int> d;
    for (int val : arr) {
        if (pos.count(val)) {
            int idx = pos[val];
            auto it = lower_bound(d.begin(), d.end(), idx);
            if (it != d.end()) {
                *it = idx;
            } else {
                d.push_back(idx);
            }
        }
    }
    return n - d.size();
}


int main() {
    vector<int> target = {5, 1, 3};
    vector<int> arr = {9, 4, 2, 3, 4};
    cout << minOperations(target, arr) << " res:2" << endl;
    vector<int> target0 = {16, 7, 20, 11, 15, 13, 10, 14, 6, 8};
    vector<int> arr0 = {11, 14, 15, 7, 5, 5, 6, 10, 11, 6};
    cout << minOperations(target0, arr0) << " res:6" << endl;
}