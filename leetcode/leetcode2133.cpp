#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <atomic>
#include <thread>

#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class TreeNode {
public:
    int val;
    TreeNode *left, *right;

    explicit TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool checkValid(vector<vector<int>> &matrix) {
        int n = matrix.size();
        vector<bool> st(n + 1, false);
        std::function<bool(void)> check = [&]() -> bool {
            for (int i = 1; i <= n; ++i) {
                if (!st[i]) return false;
            }
            return true;
        };
        // check row
        for (int i = 0; i < n; ++i) {
            fill(st.begin(), st.end(), false);
            for (int j = 0; j < n; ++j) {
                st[matrix[i][j]] = true;
            }
            if (!check()) return false;
        }
        // check col
        for (int i = 0; i < n; ++i) {
            fill(st.begin(), st.end(), false);
            for (int j = 0; j < n; ++j) {
                st[matrix[j][i]] = true;
            }
            if (!check()) return false;
        }
        return true;
    }
};