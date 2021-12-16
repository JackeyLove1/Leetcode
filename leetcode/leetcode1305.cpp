#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string_view>
#include <queue>
#include <set>
#include <cstring>
#include <cmath>

using namespace std;

template<typename T>
inline void print(vector<T> &nums) {
    for_each(nums.begin(), nums.end(), [](const T &t) { cout << t << " "; });
    cout << endl;
}


struct TreeNode {
    TreeNode *left, *right;
    int val;

    explicit TreeNode() : left(nullptr), right(nullptr), val(0) {}

    explicit TreeNode(int val_) : left(nullptr), right(nullptr), val(val_) {}

    explicit TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    priority_queue<int, vector<int>, greater<>> heap;

    void traverse(TreeNode *root) {
        if (root == nullptr) return;
        heap.push(root->val);
        if (root->left) traverse(root->left);
        if (root->right) traverse(root->right);
    }

public:
    vector<int> getAllElements(TreeNode *root1, TreeNode *root2) {
        traverse(root1);
        traverse(root2);
        vector<int> res;
        res.reserve(heap.size());
        while (!heap.empty()) {
            res.emplace_back(heap.top());
            heap.pop();
        }
        return res;
    }
};