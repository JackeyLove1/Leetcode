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

const vector<string> keyboard = {"", "", "abc", "def", "ghi",
                                 "jkl", "mno", "pqrs", "tuv", "wxyz"};

void dfs(vector<string> &res, string &path, string &digits, int idx) {
    if (idx == digits.size()) {
        res.emplace_back(path);
        return;
    }
    auto key = keyboard[digits[idx] - '0'];
    for (auto &k : key) {
        path.push_back(k);
        dfs(res, path, digits, idx + 1);
        path.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> res;
    if (digits.empty()) return res;
    string path;
    int idx = 0;
    dfs(res, path, digits, idx);
    return res;
}

int main() {
    string digits = "23";
    auto res = letterCombinations(digits);
    print(res);
}