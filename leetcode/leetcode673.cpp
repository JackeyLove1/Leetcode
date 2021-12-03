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

int findNumberOfLIS(vector<int> &nums) {
    if (nums.empty()) return 0;
    int n = nums.size();
    vector<PII> f(n + 1); // length, number
    for (int i = 0; i < n; i++) f[i] = {1, 1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                if (f[i].first > f[j].first + 1) continue;
                else if (f[i].first == f[j].first + 1) {
                    f[i].second += f[j].second;
                } else {
                    f[i].first = f[j].first + 1;
                    f[i].second = f[j].second;
                }
            }
        }
    }
    int maxLength = 1, res = 0;
    for (int i = 0; i < n; i++) {
        if (f[i].first > maxLength) {
            maxLength = f[i].first, res = f[i].second;
        } else if (f[i].first == maxLength) {
            res += f[i].second;
        } else {

        }
    }
    // print(f);
    return res;
}

int main() {
    vector<int> v1 = {1, 3, 5, 4, 7};
    cout << findNumberOfLIS(v1) << " ans is 2" << endl;
    vector<int> v2 = {2, 2, 2, 2, 2};
    cout << findNumberOfLIS(v2) << " ans is 5" << endl;
    vector<int> v3 = {1, 2, 4, 3, 5, 4, 7, 2};
    cout << findNumberOfLIS(v3) << " ans is 3" << endl;
    return 0;
}