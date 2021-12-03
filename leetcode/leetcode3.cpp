#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <tuple>


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
    cout << "ending ... " << endl;
}


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int lengthOfLongestSubstring(string s) {
    if (s.empty()) return 0;
    unordered_map<char, int> um;
    int res = 0;
    for(int i = 0, j = 0; j < s.size(); j++){
        um[s[j]]++;
        while (i < j && um[s[j]] > 1){
            --um[s[i++]];
        }
        res = max(res, j - i + 1);
    }
    return res;
}

int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << " res: 3" << endl;
    cout << lengthOfLongestSubstring("bbbbb") << " res: 1" << endl;
    cout << lengthOfLongestSubstring("pwwkew") << " res: 3" << endl;
    cout << lengthOfLongestSubstring(" ") << " res: 1" << endl;
    cout << lengthOfLongestSubstring("dvdf") << " res: 3" << endl;
}