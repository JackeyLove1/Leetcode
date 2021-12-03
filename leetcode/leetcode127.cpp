#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

class Solution {
public:
    static constexpr int N = 2e5;
    int e[N], ne[N], h[N], idx;

    void init() {
        memset(h, -1, sizeof h);
    }

    void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    }

    bool connect(string &s1, string &s2) {
        int flag = 0;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) ++flag;
        }
        return flag <= 1;
    }

    void build(vector<string> &wordList) {
        init();
        int n = wordList.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (connect(wordList[i], wordList[j])) {
                    add(i, j);
                    add(j, i);
                }
            }
        }
    }

    // 使用单向BFS
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        build(wordList);
        int cnt = 1, n = wordList.size(), endIndex = -1;
        queue<int> q;
        vector<bool> st(n + 1, false);
        for (int i = 0; i < n; i++) {
            if (connect(beginWord, wordList[i])) {
                q.push(i);
            }
            if (endWord == wordList[i]) {
                endIndex = i;
            }
        }
        if (endIndex == -1) return 0;
        while (!q.empty()) {
            int sz = q.size();
            cnt++;
            // cout << "cnt: " << cnt << " : ";
            while (sz--) {
                auto t = q.front();
                q.pop();
                // cout << wordList[t] << "  ";
                st[t] = true;
                if (t == endIndex) return cnt;
                for (int i = h[t]; i != -1; i = ne[i]) {
                    int j = e[i];
                    if (!st[j]) {
                        q.push(j);
                        st[j] = true;
                    }
                }
            }
            // cout << endl;
        }
        return 0;
    }
};

int main() {
    string begin = "hit", end = "cog";
    vector<string> lists = {"hot", "dot", "dog", "lot", "log", "cog"};
    auto s = Solution();
    cout << s.ladderLength(begin, end, lists) << " res: 5" << endl;
    return 0;
}