#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>


#pragma GCC optimize(2)

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

class Solution {
public:
    int minJumps(const vector<int> &arr) {
        if (arr.size() == 1) return 0;
        unordered_map<int, vector<int>> um;
        for (int i = 0; i < arr.size(); ++i) {
            um[arr[i]].push_back(i);
        }
        const int INF = 1e6;
        vector<int> f(arr.size() + 10, -1);
        std::function<int(int)> dfs = [&](int x) -> int {
            if (x == arr.size() - 1) return 0;
            int &v = f[x];
            if (v != -1 && v != INF) return v;
            v = INF;
            if (x + 1 < arr.size()) v = min(v, dfs(x + 1) + 1);
            if (x - 1 >= 0) v = min(v, dfs(x - 1) + 1);
            for (const auto &idx : um[arr[x]]) {
                if (idx == x) continue;
                v = min(v, dfs(idx) + 1);
            }
            // cout << "x: " << x << " arr[x]: " << arr[x] << " res: " << v << endl;
            return v;
        };
        return dfs(0);
    }
};

int main() {
    Solution s;
    vector<int> v1 = {100, -23, -23, 404, 100, 23, 23, 23, 3, 404};
    cout << s.minJumps(v1) << " res: 3" << endl;
    vector<int> v2 = {-76, 3, 66, -32, 64, 2, -19, -8, -5, -93, 80, -5, -76, -78, 64, 2, 16};
    cout << s.minJumps(v2) << " res: 5" << endl;
}