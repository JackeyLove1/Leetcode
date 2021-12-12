#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


class Solution1 { // wrong
private:
    vector<vector<int>> f;
public:
    bool isABC(const string &s, int l, int r) {
        if (l > r) return true;
        int &v = f[l][r];
        if (v != -1) return v;
        v = 0;
        // 分四种情况讨论
        if (s[l] == 'a' && s[l + 1] == 'b' && s[l + 2] == 'c') {
            v = v || isABC(s, l + 3, r);
        }
        if (s[l] == 'a' && s[l + 1] == 'b' && s[r] == 'c') {
            v = v || isABC(s, l + 2, r - 1);
        }
        if (s[l] == 'a' && s[r - 1] == 'b' && s[r] == 'c') {
            v = v || isABC(s, l + 1, r - 2);
        }
        if (s[r - 2] == 'a' && s[r - 1] == 'b' && s[r] == 'c') {
            v = v || isABC(s, l, r - 3);
        }
        return v;
    }

    bool isValid(string s) {
        // 使用递归判断法
        if (s.size() % 3 != 0) return false;
        int size_ = s.size() + 10;
        f = vector<vector<int>>(size_, vector<int>(size_, -1));
        s = static_cast<const string>(s);
        return isABC(s, 0, s.size() - 1);
    }
};

class Solution2 { //wrong
public:
    bool isValid(string s) {
        if (s.size() % 3 != 0) return false;
        vector<int> a_index, b_index, c_index;
        s = static_cast<const string>(s);
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'a') a_index.push_back(i);
            if (s[i] == 'b') b_index.push_back(i);
            if (s[i] == 'c') c_index.push_back(i);
        }
        int size_ = a_index.size();
        if (b_index.size() != size_ || c_index.size() != size_) return false;
        for (int i = 0; i < size_; ++i) {
            if (a_index[i] < b_index[i] && b_index[i] < c_index[i]) continue;
            return false;
        }
        return true;
    }
};

class Solution3 {
public:
    bool isValid(string s) {
        if (s.size() % 3 != 0) return false;
        s = static_cast<const string>(s);
        unordered_map<char, int> count;
        for (auto &ch : s) {
            ++count[ch];
        }
        if (count['a'] != count['b'] && count['a'] != count['c']) {
            return false;
        }
        const string abc = "abc";
        while (!s.empty()) {
            auto pos = s.find(abc);
            if (pos == string::npos) {
                return false;
            }
            s.erase(pos, 3);
        }
        return true;
    }
};
int main() {
    Solution s;
    cout << s.isValid("abccba") << " res: 0" << endl;
    cout << s.isValid("abc") << " res: 1" << endl;
    cout << s.isValid("abcabcababcc") << " res: 1" << endl;
    cout << s.isValid("aabcbabcc") << " res: 1" << endl;
}