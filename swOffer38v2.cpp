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

void dfs(vector<string> &res, set<string> &set1, string &s, int start) {
    if (start == s.size()) {
        if (set1.count(s)) return;
        res.emplace_back(s);
        set1.insert(s);
        return;
    }
    for (int i = start; i < s.size(); i++) {
        swap(s[start], s[i]);
        dfs(res, set1, s, start + 1);
        swap(s[start], s[i]);
    }
}

vector<string> permutation(string s) {
    vector<string> res;
    set<string> set1;
    int start = 0;
    dfs(res, set1, s, start);
    return res;
}