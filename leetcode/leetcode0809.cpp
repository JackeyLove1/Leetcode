#include <iostream>
#include <utility>
#include <future>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
private:
    vector<string> res;

    void dfs(int n, int pos, int neg, string &path) {
        if (pos > n || neg > n || neg > pos) {
            return;
        }

        // backtrace
        // cout << "cur path: " << path << " p: " << pos << " n:" << neg << endl;
        if (pos == n && neg == n) {
            res.push_back(path);
        }
        path.push_back('(');
        dfs(n, pos + 1, neg, path);
        path.pop_back();

        path.push_back(')');
        dfs(n, pos, neg + 1, path);
        path.pop_back();

    }

public:
    vector<string> generateParenthesis(int n) {
        string path;
        dfs(n, 0, 0, path);
        return res;
    }
};

int main() {
    Solution s;
    auto res = s.generateParenthesis(3);
    print(res);
}