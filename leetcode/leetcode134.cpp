#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>

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
    cout << "ending .... " << endl;
}

using PII = pair<int, int>;

inline void print(vector<PII> &nums) {
    for (auto &num : nums) {
        cout << num.first << " " << num.second << endl;
    }
}

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int res = -1, n = gas.size();
    vector<int> diff(n);
    for (int i = 0; i < n; i++) {
        diff[i] = gas[i] - cost[i];
    }
    for (int i = 0; i < n; i++) {
        if (diff[i] < 0) continue;
        int sum = diff[i], cnt = 1;
        for (int j = 1; j < n; j++) {
            sum += diff[(i + j) % n];
            if (sum < 0) break;
            cnt++;
        }
        if (cnt == n) return i;
    }
    return -1;
}

int main() {
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};
    cout << canCompleteCircuit(gas, cost) << endl;
}