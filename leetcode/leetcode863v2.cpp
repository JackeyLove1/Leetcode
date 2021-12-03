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
    static constexpr int N = 1e4;
    int e[N], ne[N], h[N], idx;

    void init() {
        memset(h, -1, sizeof h);
        idx = 0;
    }

    void add(int a, int b) {
        e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    }

    void build(TreeNode *root) {
        if (root == nullptr) return;
        int val = root->val;
        if (root->left) {
            add(val, root->left->val);
            add(root->left->val, val);
            build(root->left);
        }
        if (root->right) {
            add(val, root->right->val);
            add(root->right->val, val);
            build(root->right);
        }
    }

    vector<int> distanceK(TreeNode *root, TreeNode *target, int k) {
        init();
        vector<int> res;
        build(root);
        int ver = target->val;
        unordered_set<int> st;
        queue<int> q;
        q.push(ver);
        st.insert(ver);
        while (q.size() && k >= 0) {
            int sz = q.size();
            while (sz--) {
                auto t = q.front();
                q.pop();
                if (!k) {
                    res.push_back(t);
                    continue;
                }
                for (int i = h[t]; i != -1; i = ne[i]) {
                    int j = e[i];
                    if (!st.count(j)) {
                        q.push(j);
                        st.insert(j);
                    }
                }
            }
            --k;
        }
        return res;
    }
};