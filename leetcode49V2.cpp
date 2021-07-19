#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template<typename T>
inline void print(vector<T> &nums) {
    for (auto &num : nums) cout << num << " ";
    // cout << "end..." << endl;
}

template<typename T>
inline void print(vector<vector<T>> &nums) {
    for (auto &num : nums) {
        for (auto &n : num) {
            cout << n << " ";
        }
        cout << endl;
    }
    cout << "end ... " << endl;
}

vector<vector<string>> groupAnagrams(vector<string> &strs) {
    vector<vector<string>> res;
    if (strs.empty()) return res;
    unordered_map<string, vector<string>> um;
    for (auto &str : strs) {
        auto tmp = str.substr(0);
        sort(tmp.begin(), tmp.end());
        um[tmp].push_back(str);
    }
    for (auto&[_, v] :um) {
        res.emplace_back(v);
    }
    return res;
}

int main() {
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto res = groupAnagrams(strs);
    // for_each(res.begin(), res.end(), print);
    print(res);
}
