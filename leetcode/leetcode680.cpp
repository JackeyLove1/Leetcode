#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>


using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    bool validPalindrome(string s) {
        // 双指针解法
        string_view sv(s);
        std::function<bool(int, int)> check = [&](int cl, int cr) -> bool {
            for (; cl < cr; ++cl, --cr) {
                if (sv[cl] != sv[cr]) return false;
            }
            return true;
        };
        int l = 0, r = s.size() - 1;
        for (; l < r; ++l, --r) {
            if (sv[l] == sv[r]) continue;
            else {
                return check(l + 1, r) || check(l, r - 1);
            }
        }
        return true;
    }
};

class Solution1 {
public:
    bool validPalindrome(string s) {
        // s.size() - s中最长子回文串长度 <= 1
        // 使用记忆话搜索的方法
        int n = s.size();
        vector<vector<int>> f(n + 10, vector<int>(n + 10, -1));
        for (int i = 0; i < s.size(); ++i) f[i][i] = 1;
        std::function<int(int, int)> dfs = [&](int l, int r) -> int {
            if (l > r)return 0;
            int &v = f[l][r];
            if (v != -1) return v;
            if (s[l] == s[r]) {
                v = max(v, dfs(l + 1, r - 1) + 2);
            }
            v = max({v, dfs(l + 1, r), dfs(l, r - 1)});
            return v;
        };
        int sub_size = dfs(0, n - 1);
        return s.size() - sub_size <= 1;
    }
};

int main() {
    Solution s;
    cout << s.validPalindrome("aba") << " res:1" << endl;
    cout << s.validPalindrome("abca") << " res: 1" << endl;
    cout << s.validPalindrome("abc") << " res: 0" << endl;
}