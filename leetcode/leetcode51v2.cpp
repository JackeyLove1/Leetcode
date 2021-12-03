#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
        cout << endl;
    }
}

template<typename T>
inline void print(vector<T> &num) {
    for_each(num.begin(), num.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    static constexpr int debug = 0;
    int N = 0;
    vector<int> states;
    set<vector<int>> s;
    function<bool(int, int, int, int)> check;
    vector<vector<string>> g;

    void add(const vector<int> &path) {
        vector<string> tmp;
        for (auto &state : path) {
            string res = "";
            for (int i = 0; i < N; i++) {
                if (state & (1 << i)) res += 'Q';
                else res += '.';
            }
            tmp.emplace_back(res);
        }
        g.emplace_back(tmp);
    }

    void dfs(int cur, vector<int> &path) {
        if (path.size() == N) {
            if (!s.count(path)) {
                s.insert(path);
                add(path);
                // if (debug) print(path);
            }
            return;
        }
        if (path.empty()) {
            for (auto &state : states) {
                path.push_back(state);
                dfs(cur + 1, path);
                path.pop_back();
            }
        }

        for (auto &state : states) {
            bool c = true;
            for (int i = 0; i < path.size(); i++) {
                c = c & check(path[i], i, state, cur);
            }
            if (c) {
                path.push_back(state);
                dfs(cur + 1, path);
                path.pop_back();
            }
        }
    };

    vector<vector<string>> solveNQueens(int n) {
        if (n == 1) return {{"Q"}};
        // 检查两个状态是否相融
        // 检查是否同一斜
        check = [](int s1, int i, int s2, int j) -> bool {
            int diff = abs(i - j);
            return !(s1 & (s2 << diff)) && !(s1 & (s2 >> diff)) && !(s1 & s2);
        };

        states.reserve(n + 1);
        for (int i = 0; i < n; i++) {
            states.push_back(1 << i);
        }

        N = n;
        vector<int> path;
        path.reserve(n + 1);
        dfs(0, path);
        return g;
    }
};

int main() {
    auto s = Solution();
    auto g = s.solveNQueens(4);
    print(g);
    return 0;
}