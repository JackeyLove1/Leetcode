#include <iostream>
// #include "Logger.h"

using namespace std;

#include <unordered_map>
#include <map>
#include <set>

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution {
public:
    vector<string> generateParenthesis(int n) {
        int left = n, right = n;
        vector<string> res;
        std::function<void(int, int, string &)> dfs = [&]
                (int cur_left, int cur_right, string &path) {
            if (cur_left > n || cur_right > n || cur_right > cur_left) {
                return;
            }
            if (cur_left == n && cur_right == n) {
                res.push_back(path);
                return;
            }

            // backtrace
            path.push_back('(');
            dfs(cur_left + 1, cur_right, path);
            path.pop_back();

            path.push_back(')');
            dfs(cur_left, cur_right + 1, path);
            path.pop_back();
        };
        string path;
        dfs(0, 0, path);
        return res;
    }
};


int main() {
    Solution s;
    auto v1 = s.generateParenthesis(3);
    print(v1);
}