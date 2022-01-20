#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <tuple>
#include <list>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

#pragma GCC optimize(2)

using namespace std;

inline void fhj() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

template<typename T>
static inline void print(const vector<T> &nums) {
    if (nums.empty()) {
        cout << " empty !" << endl;
        return;
    }
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}

inline int count(int state) {
    return __builtin_popcount(state);
}

class TreeNode {
public:
    int val;
    TreeNode *left, *right;

    explicit TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    constexpr static int N = 110;
    int depth[N], parent[N];
public:
    void dfs(TreeNode *u, int fa) {
        parent[u->val] = fa;
        depth[u->val] = depth[fa] + 1;
        if (u->left) dfs(u->left, u->val);
        if (u->right) dfs(u->right, u->val);
    }

    bool isCousins(TreeNode *root, int x, int y) {
        memset(depth, 0, sizeof depth);
        memset(parent, 0, sizeof parent);
        depth[0] = 0; // super node
        if (root == nullptr) return false;
        dfs(root, 0);
        return depth[x] == depth[y] && parent[x] != parent[y];
    }
};